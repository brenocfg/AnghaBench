#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_6__ ;
typedef  struct TYPE_15__   TYPE_5__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_14__ {int hashLog3; int /*<<< orphan*/  loadedDictEnd; int /*<<< orphan*/  nextToUpdate; int /*<<< orphan*/  window; int /*<<< orphan*/ * hashTable3; int /*<<< orphan*/ * chainTable; int /*<<< orphan*/ * hashTable; } ;
typedef  TYPE_4__ ZSTD_matchState_t ;
typedef  int /*<<< orphan*/  ZSTD_frameParameters ;
typedef  int /*<<< orphan*/  ZSTD_customMem ;
typedef  int /*<<< orphan*/  ZSTD_buffered_policy_e ;
struct TYPE_11__ {scalar_t__ windowLog; scalar_t__ strategy; size_t hashLog; size_t chainLog; } ;
struct TYPE_15__ {int /*<<< orphan*/  fParams; TYPE_1__ cParams; } ;
typedef  TYPE_5__ ZSTD_CCtx_params ;
struct TYPE_13__ {int /*<<< orphan*/ * prevCBlock; TYPE_4__ matchState; } ;
struct TYPE_12__ {TYPE_1__ cParams; } ;
struct TYPE_16__ {scalar_t__ stage; TYPE_3__ blockState; int /*<<< orphan*/  dictID; int /*<<< orphan*/  workspace; TYPE_2__ appliedParams; TYPE_5__ requestedParams; int /*<<< orphan*/  customMem; } ;
typedef  TYPE_6__ ZSTD_CCtx ;
typedef  int /*<<< orphan*/  U64 ;
typedef  int /*<<< orphan*/  U32 ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUGLOG (int,char*) ; 
 int /*<<< orphan*/  RETURN_ERROR_IF (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ZSTD_cwksp_mark_tables_clean (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ZSTD_cwksp_mark_tables_dirty (int /*<<< orphan*/ *) ; 
 scalar_t__ ZSTD_fast ; 
 int /*<<< orphan*/  ZSTD_resetCCtx_internal (TYPE_6__*,TYPE_5__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ZSTDcrp_leaveDirty ; 
 scalar_t__ ZSTDcs_init ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,size_t const) ; 
 int /*<<< orphan*/  stage_wrong ; 

__attribute__((used)) static size_t ZSTD_copyCCtx_internal(ZSTD_CCtx* dstCCtx,
                            const ZSTD_CCtx* srcCCtx,
                            ZSTD_frameParameters fParams,
                            U64 pledgedSrcSize,
                            ZSTD_buffered_policy_e zbuff)
{
    DEBUGLOG(5, "ZSTD_copyCCtx_internal");
    RETURN_ERROR_IF(srcCCtx->stage!=ZSTDcs_init, stage_wrong);

    memcpy(&dstCCtx->customMem, &srcCCtx->customMem, sizeof(ZSTD_customMem));
    {   ZSTD_CCtx_params params = dstCCtx->requestedParams;
        /* Copy only compression parameters related to tables. */
        params.cParams = srcCCtx->appliedParams.cParams;
        params.fParams = fParams;
        ZSTD_resetCCtx_internal(dstCCtx, params, pledgedSrcSize,
                                ZSTDcrp_leaveDirty, zbuff);
        assert(dstCCtx->appliedParams.cParams.windowLog == srcCCtx->appliedParams.cParams.windowLog);
        assert(dstCCtx->appliedParams.cParams.strategy == srcCCtx->appliedParams.cParams.strategy);
        assert(dstCCtx->appliedParams.cParams.hashLog == srcCCtx->appliedParams.cParams.hashLog);
        assert(dstCCtx->appliedParams.cParams.chainLog == srcCCtx->appliedParams.cParams.chainLog);
        assert(dstCCtx->blockState.matchState.hashLog3 == srcCCtx->blockState.matchState.hashLog3);
    }

    ZSTD_cwksp_mark_tables_dirty(&dstCCtx->workspace);

    /* copy tables */
    {   size_t const chainSize = (srcCCtx->appliedParams.cParams.strategy == ZSTD_fast) ? 0 : ((size_t)1 << srcCCtx->appliedParams.cParams.chainLog);
        size_t const hSize =  (size_t)1 << srcCCtx->appliedParams.cParams.hashLog;
        int const h3log = srcCCtx->blockState.matchState.hashLog3;
        size_t const h3Size = h3log ? ((size_t)1 << h3log) : 0;

        memcpy(dstCCtx->blockState.matchState.hashTable,
               srcCCtx->blockState.matchState.hashTable,
               hSize * sizeof(U32));
        memcpy(dstCCtx->blockState.matchState.chainTable,
               srcCCtx->blockState.matchState.chainTable,
               chainSize * sizeof(U32));
        memcpy(dstCCtx->blockState.matchState.hashTable3,
               srcCCtx->blockState.matchState.hashTable3,
               h3Size * sizeof(U32));
    }

    ZSTD_cwksp_mark_tables_clean(&dstCCtx->workspace);

    /* copy dictionary offsets */
    {
        const ZSTD_matchState_t* srcMatchState = &srcCCtx->blockState.matchState;
        ZSTD_matchState_t* dstMatchState = &dstCCtx->blockState.matchState;
        dstMatchState->window       = srcMatchState->window;
        dstMatchState->nextToUpdate = srcMatchState->nextToUpdate;
        dstMatchState->loadedDictEnd= srcMatchState->loadedDictEnd;
    }
    dstCCtx->dictID = srcCCtx->dictID;

    /* copy block state */
    memcpy(dstCCtx->blockState.prevCBlock, srcCCtx->blockState.prevCBlock, sizeof(*srcCCtx->blockState.prevCBlock));

    return 0;
}