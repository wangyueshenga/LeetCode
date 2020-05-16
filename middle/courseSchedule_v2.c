/* 210. 课程表 II
现在你总共有 n 门课需要选，记为 0 到 n-1。

在选修某些课程之前需要一些先修课程。 例如，想要学习课程 0 ，你需要先完成课程 1 ，我们用一个匹配来表示他们: [0,1]

给定课程总量以及它们的先决条件，返回你为了学完所有课程所安排的学习顺序。

可能会有多个正确的顺序，你只要返回一种就可以了。如果不可能完成所有课程，返回一个空数组。

示例 1:

输入: 2, [[1,0]] 
输出: [0,1]
解释: 总共有 2 门课程。要学习课程 1，你需要先完成课程 0。因此，正确的课程顺序为 [0,1] 。
示例 2:

输入: 4, [[1,0],[2,0],[3,1],[3,2]]
输出: [0,1,2,3] or [0,2,1,3]
解释: 总共有 4 门课程。要学习课程 3，你应该先完成课程 1 和课程 2。并且课程 1 和课程 2 都应该排在课程 0 之后。
     因此，一个正确的课程顺序是 [0,1,2,3] 。另一个正确的排序是 [0,2,1,3] 。
说明:

输入的先决条件是由边缘列表表示的图形，而不是邻接矩阵。详情请参见图的表示法。
你可以假定输入的先决条件中没有重复的边。
提示:

这个问题相当于查找一个循环是否存在于有向图中。如果存在循环，则不存在拓扑排序，因此不可能选取所有课程进行学习。
通过 DFS 进行拓扑排序 - 一个关于Coursera的精彩视频教程（21分钟），介绍拓扑排序的基本概念。
拓扑排序也可以通过 BFS 完成。 */

#include "../public.h"
#define SIZE 1024
int *findOrder(int, int **, int, int *, int *);


int main(int argc, char *argv[])
{
    int numCourses = 4;
    int **prerequisites ;
    int array[8] = {1,0,2,0,3,1,3,2};
    prerequisites = (int **) malloc(sizeof(int *) * 4);
    int count = 0;
    printf("initlize: \n");
    for(count = 0; count < 4; ++count){
        prerequisites[4] = (int *)malloc(sizeof(int) * 2);
        printf("- ");
    }

    int count2 = 0;
    printf("\nInitlize input array:\n");
    for(count = 0; count < 4; ++count){
        for(count2 = 0; count2 < 2; ++count2){
            prerequisites[count][count2] = array[count*4+count2];
        }
    }
    int prerequisitesSize = 4 ;
    int *prerequisitesColSize = NULL;
    * prerequisitesColSize = 4;
    int *returnSize = 0;
    printf("call function\n");
    int * result = findOrder(numCourses, prerequisites, prerequisitesSize, prerequisitesColSize, returnSize);
    if(result != NULL){
        // int count;
        printf(
        "%d", *returnSize
        );
        for(count = 0; count < *returnSize; ++count){
            printf("%d ",*(result+count));
        }
        free(result);
    }else{
        printf("%s","fail~\n");
    }
    return 0;
}
/**
 * numCourses 课程总数
 * prerequisites 课程前置关系
 * prerequisitesSize 前置课程规模
 * prerequisitesColSize
 * returnSize 返回数组规模
  */

int *findOrder(int numCourses, int **prerequisites, int prerequisitesSize, int *prerequisitesColSize, int *returnSize)
{

    int a[SIZE];
    int i, j, *ret = (int *)malloc(sizeof(int) * numCourses), top = 0;
    memset(ret, 0, numCourses ); //使用0 初始化 数组
    memset(a, 0, sizeof(a));

    /**
     * 记录图节点入度
     */
    for (i = 0; i < prerequisitesSize; ++i)
    {
        a[prerequisites[i][0]]++;
    }

    /**
     * 入度为0的节点 即为 可 存放至任意位置的点 入度记录为-1 节点 为 不存在于输入 数组中的 虚节点
      */
    for (i = 0; i < numCourses; i++)
    {
        if (a[i] == 0)
        {
            ret[top++] = i;
        }
    }

    /** 
     * 处理入度非零节点
     */
    for ( i = 0; i < numCourses; ++i)
    {
        for(j = 0; j < prerequisitesSize; ++j){
            if(prerequisites[j][0] != -1 && a[prerequisites[j][0]] > 0 && a[prerequisites[j][1]] == 0){
                a[prerequisites[j][0]]-- ;
                if(a[prerequisites[j][0]] == 0){
                    ret[++top] = prerequisites[j][0];
                }
                prerequisites[j][0] = -1;
            }
        }
    }

    if(numCourses != top){
        *returnSize = 0;
        free(ret);
        ret = NULL;
    }else{
        *returnSize = numCourses;
    }

    return ret;
}