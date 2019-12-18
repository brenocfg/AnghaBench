#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint8_t ;
typedef  scalar_t__ uint32_t ;
typedef  scalar_t__ t_Handle ;
typedef  int /*<<< orphan*/  t_Error ;
struct TYPE_7__ {int flags; scalar_t__ bpid; int spMaxBufs; int /*<<< orphan*/  numOfBuffers; int /*<<< orphan*/  h_BmPortal; struct TYPE_7__* p_BmPoolDriverParams; struct bm_buffer* sp; int /*<<< orphan*/  depletionThresholds; int /*<<< orphan*/  h_Bm; scalar_t__ useDepletion; int /*<<< orphan*/  shadowMode; scalar_t__ useStockpile; scalar_t__ dynamicBpid; } ;
typedef  TYPE_1__ t_BmPool ;
struct bm_buffer {int dummy; } ;

/* Variables and functions */
 int BMAN_POOL_FLAG_DEPLETION ; 
 int BMAN_POOL_FLAG_DYNAMIC_BPID ; 
 int BMAN_POOL_FLAG_STOCKPILE ; 
 int /*<<< orphan*/  BM_POOL_FillBufs (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BM_POOL_Free (TYPE_1__*) ; 
 scalar_t__ BmBpidGet (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ BmSetPoolThresholds (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CRITICAL ; 
 int /*<<< orphan*/  E_INVALID_HANDLE ; 
 int /*<<< orphan*/  E_INVALID_STATE ; 
 int /*<<< orphan*/  E_NO_MEMORY ; 
 int /*<<< orphan*/  E_OK ; 
 int /*<<< orphan*/  FALSE ; 
 scalar_t__ ILLEGAL_BASE ; 
 int /*<<< orphan*/  MAJOR ; 
 char* NO_MSG ; 
 int /*<<< orphan*/  RETURN_ERROR (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  SANITY_CHECK_RETURN_ERROR (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  XX_Free (TYPE_1__*) ; 
 scalar_t__ XX_Malloc (int) ; 
 int /*<<< orphan*/  depletion_link (TYPE_1__*) ; 
 int /*<<< orphan*/  memset (struct bm_buffer*,int /*<<< orphan*/ ,int) ; 

t_Error BM_POOL_Init(t_Handle h_BmPool)
{
    t_BmPool        *p_BmPool = (t_BmPool *)h_BmPool;
    t_Error         err;

    SANITY_CHECK_RETURN_ERROR(p_BmPool, E_INVALID_HANDLE);
    SANITY_CHECK_RETURN_ERROR(p_BmPool->p_BmPoolDriverParams, E_INVALID_HANDLE);

    p_BmPool->flags |= (p_BmPool->p_BmPoolDriverParams->dynamicBpid)?BMAN_POOL_FLAG_DYNAMIC_BPID:0;
    p_BmPool->flags |= (p_BmPool->p_BmPoolDriverParams->useStockpile)?BMAN_POOL_FLAG_STOCKPILE:0;
    p_BmPool->flags |= ((!p_BmPool->shadowMode) &&
                        (p_BmPool->p_BmPoolDriverParams->useDepletion))?BMAN_POOL_FLAG_DEPLETION:0;

    if (p_BmPool->flags & BMAN_POOL_FLAG_DYNAMIC_BPID)
    {
        if((p_BmPool->bpid = (uint8_t)BmBpidGet(p_BmPool->h_Bm, FALSE, (uint32_t)0)) == (uint8_t)ILLEGAL_BASE)
        {
            BM_POOL_Free(p_BmPool);
            RETURN_ERROR(CRITICAL, E_INVALID_STATE, ("can't allocate new dynamic pool id"));
        }
    }
    else
    {
        if (BmBpidGet(p_BmPool->h_Bm, TRUE, (uint32_t)p_BmPool->bpid) == (uint32_t)ILLEGAL_BASE)
        {
            BM_POOL_Free(p_BmPool);
            RETURN_ERROR(CRITICAL, E_INVALID_STATE, ("can't force pool id %d", p_BmPool->bpid));
        }
    }
    if (p_BmPool->flags & BMAN_POOL_FLAG_DEPLETION)
    {
        if(BmSetPoolThresholds(p_BmPool->h_Bm, p_BmPool->bpid, p_BmPool->p_BmPoolDriverParams->depletionThresholds))
        {
            BM_POOL_Free(p_BmPool);
            RETURN_ERROR(MAJOR, E_INVALID_STATE, ("can't set thresh for pool bpid %d",p_BmPool->bpid));
        }

        depletion_link(p_BmPool);
    }

    if (p_BmPool->flags & BMAN_POOL_FLAG_STOCKPILE)
    {
        p_BmPool->sp = (struct bm_buffer *)XX_Malloc(sizeof(struct bm_buffer) * p_BmPool->spMaxBufs);
        if (!p_BmPool->sp)
        {
            BM_POOL_Free(p_BmPool);
            RETURN_ERROR(MAJOR, E_NO_MEMORY, ("Bm Pool Stockpile"));
        }
        memset(p_BmPool->sp, 0, sizeof(struct bm_buffer) * p_BmPool->spMaxBufs);
    }

    XX_Free(p_BmPool->p_BmPoolDriverParams);
    p_BmPool->p_BmPoolDriverParams = NULL;

    /*******************/
    /* Create buffers  */
    /*******************/
    if ((err = BM_POOL_FillBufs (p_BmPool, p_BmPool->h_BmPortal, p_BmPool->numOfBuffers)) != E_OK)
    {
        BM_POOL_Free(p_BmPool);
        RETURN_ERROR(MAJOR, err, NO_MSG);
    }

    return E_OK;
}