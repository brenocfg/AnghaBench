#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  size_t uint8_t ;
typedef  scalar_t__ uint16_t ;
struct TYPE_5__ {int numOfPoolsUsed; TYPE_1__* extBufPool; } ;
typedef  TYPE_2__ t_FmExtPools ;
struct TYPE_4__ {scalar_t__ size; size_t id; } ;

/* Variables and functions */

void FmSpSetBufPoolsInAscOrderOfBufSizes(t_FmExtPools   *p_FmExtPools,
                                         uint8_t        *orderedArray,
                                         uint16_t       *sizesArray)
{
    uint16_t                    bufSize = 0;
    int                         i=0, j=0, k=0;

    /* First we copy the external buffers pools information to an ordered local array */
    for (i=0;i<p_FmExtPools->numOfPoolsUsed;i++)
    {
        /* get pool size */
        bufSize = p_FmExtPools->extBufPool[i].size;

        /* keep sizes in an array according to poolId for direct access */
        sizesArray[p_FmExtPools->extBufPool[i].id] =  bufSize;

        /* save poolId in an ordered array according to size */
        for (j=0;j<=i;j++)
        {
            /* this is the next free place in the array */
            if (j==i)
                orderedArray[i] = p_FmExtPools->extBufPool[i].id;
            else
            {
                /* find the right place for this poolId */
                if (bufSize < sizesArray[orderedArray[j]])
                {
                    /* move the poolIds one place ahead to make room for this poolId */
                    for (k=i;k>j;k--)
                       orderedArray[k] = orderedArray[k-1];

                    /* now k==j, this is the place for the new size */
                    orderedArray[k] = p_FmExtPools->extBufPool[i].id;
                    break;
                }
            }
        }
    }
}