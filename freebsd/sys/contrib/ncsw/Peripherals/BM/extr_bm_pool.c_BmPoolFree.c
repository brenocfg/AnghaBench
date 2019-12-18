#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  t_Handle ;
typedef  int /*<<< orphan*/  t_Error ;
struct TYPE_9__ {int /*<<< orphan*/  h_BufferPool; int /*<<< orphan*/  (* f_PutBuf ) (int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ) ;} ;
struct TYPE_10__ {int flags; struct TYPE_10__* sp; int /*<<< orphan*/  bpid; int /*<<< orphan*/  h_Bm; TYPE_1__ bufferPoolInfo; int /*<<< orphan*/  h_BmPortal; int /*<<< orphan*/  shadowMode; } ;
typedef  TYPE_2__ t_BmPool ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT_COND (TYPE_2__*) ; 
 int BMAN_POOL_FLAG_DEPLETION ; 
 void* BM_POOL_GetBuf (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BM_POOL_GetBufferContext (TYPE_2__*,void*) ; 
 int /*<<< orphan*/  BmBpidPut (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BmUnSetPoolThresholds (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  E_OK ; 
 scalar_t__ TRUE ; 
 int /*<<< orphan*/  XX_Free (TYPE_2__*) ; 
 int /*<<< orphan*/  depletion_unlink (TYPE_2__*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static t_Error BmPoolFree(t_BmPool *p_BmPool, bool discardBuffers)
{
    t_Handle    h_BufContext;
    void        *p_Data;

    ASSERT_COND(p_BmPool);

    if (!p_BmPool->shadowMode)
    {
        if (p_BmPool->flags & BMAN_POOL_FLAG_DEPLETION)
        {
            depletion_unlink(p_BmPool);
            BmUnSetPoolThresholds(p_BmPool->h_Bm, p_BmPool->bpid);
        }
        while (TRUE)
        {
            p_Data = BM_POOL_GetBuf(p_BmPool, p_BmPool->h_BmPortal);
            if (!p_Data)
                break;
            h_BufContext = BM_POOL_GetBufferContext(p_BmPool, p_Data);
            if (!discardBuffers)
                p_BmPool->bufferPoolInfo.f_PutBuf(p_BmPool->bufferPoolInfo.h_BufferPool, p_Data, h_BufContext);
        }
        BmBpidPut(p_BmPool->h_Bm, p_BmPool->bpid);
    }

    if (p_BmPool->sp)
        XX_Free(p_BmPool->sp);

    XX_Free(p_BmPool);

    return E_OK;
}