#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ ZSTD_resetTarget_e ;
typedef  int /*<<< orphan*/  ZSTD_optimal_t ;
typedef  int /*<<< orphan*/  ZSTD_match_t ;
struct TYPE_10__ {scalar_t__ strategy; size_t chainLog; size_t hashLog; int minMatch; int /*<<< orphan*/  windowLog; } ;
struct TYPE_8__ {unsigned int* litFreq; unsigned int* litLengthFreq; unsigned int* matchLengthFreq; unsigned int* offCodeFreq; int /*<<< orphan*/ * priceTable; int /*<<< orphan*/ * matchTable; } ;
struct TYPE_11__ {int dictLimit; int lowLimit; scalar_t__ base; scalar_t__ nextSrc; } ;
struct TYPE_9__ {int hashLog3; int* hashTable; int* chainTable; int* hashTable3; TYPE_3__ cParams; TYPE_1__ opt; TYPE_4__ window; } ;
typedef  TYPE_2__ ZSTD_matchState_t ;
typedef  scalar_t__ ZSTD_indexResetPolicy_e ;
typedef  int /*<<< orphan*/  ZSTD_cwksp ;
typedef  TYPE_3__ ZSTD_compressionParameters ;
typedef  scalar_t__ ZSTD_compResetPolicy_e ;
typedef  int U32 ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUGLOG (int,char*,...) ; 
 int Litbits ; 
 int MIN (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int MaxLL ; 
 int MaxML ; 
 int MaxOff ; 
 int /*<<< orphan*/  RETURN_ERROR_IF (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ZSTD_HASHLOG3_MAX ; 
 int ZSTD_OPT_NUM ; 
 scalar_t__ ZSTD_btopt ; 
 int /*<<< orphan*/  ZSTD_cwksp_clean_tables (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ZSTD_cwksp_clear_tables (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ZSTD_cwksp_mark_tables_dirty (int /*<<< orphan*/ *) ; 
 scalar_t__ ZSTD_cwksp_reserve_aligned (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  ZSTD_cwksp_reserve_failed (int /*<<< orphan*/ *) ; 
 scalar_t__ ZSTD_cwksp_reserve_table (int /*<<< orphan*/ *,size_t const) ; 
 scalar_t__ ZSTD_fast ; 
 int /*<<< orphan*/  ZSTD_invalidateMatchState (TYPE_2__*) ; 
 scalar_t__ const ZSTD_resetTarget_CCtx ; 
 scalar_t__ const ZSTDcrp_leaveDirty ; 
 scalar_t__ const ZSTDirp_reset ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  memory_allocation ; 
 int /*<<< orphan*/  memset (TYPE_4__*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static size_t
ZSTD_reset_matchState(ZSTD_matchState_t* ms,
                      ZSTD_cwksp* ws,
                const ZSTD_compressionParameters* cParams,
                const ZSTD_compResetPolicy_e crp,
                const ZSTD_indexResetPolicy_e forceResetIndex,
                const ZSTD_resetTarget_e forWho)
{
    size_t const chainSize = (cParams->strategy == ZSTD_fast) ? 0 : ((size_t)1 << cParams->chainLog);
    size_t const hSize = ((size_t)1) << cParams->hashLog;
    U32    const hashLog3 = ((forWho == ZSTD_resetTarget_CCtx) && cParams->minMatch==3) ? MIN(ZSTD_HASHLOG3_MAX, cParams->windowLog) : 0;
    size_t const h3Size = hashLog3 ? ((size_t)1) << hashLog3 : 0;

    DEBUGLOG(4, "reset indices : %u", forceResetIndex == ZSTDirp_reset);
    if (forceResetIndex == ZSTDirp_reset) {
        memset(&ms->window, 0, sizeof(ms->window));
        ms->window.dictLimit = 1;    /* start from 1, so that 1st position is valid */
        ms->window.lowLimit = 1;     /* it ensures first and later CCtx usages compress the same */
        ms->window.nextSrc = ms->window.base + 1;   /* see issue #1241 */
        ZSTD_cwksp_mark_tables_dirty(ws);
    }

    ms->hashLog3 = hashLog3;

    ZSTD_invalidateMatchState(ms);

    assert(!ZSTD_cwksp_reserve_failed(ws)); /* check that allocation hasn't already failed */

    ZSTD_cwksp_clear_tables(ws);

    DEBUGLOG(5, "reserving table space");
    /* table Space */
    ms->hashTable = (U32*)ZSTD_cwksp_reserve_table(ws, hSize * sizeof(U32));
    ms->chainTable = (U32*)ZSTD_cwksp_reserve_table(ws, chainSize * sizeof(U32));
    ms->hashTable3 = (U32*)ZSTD_cwksp_reserve_table(ws, h3Size * sizeof(U32));
    RETURN_ERROR_IF(ZSTD_cwksp_reserve_failed(ws), memory_allocation,
                    "failed a workspace allocation in ZSTD_reset_matchState");

    DEBUGLOG(4, "reset table : %u", crp!=ZSTDcrp_leaveDirty);
    if (crp!=ZSTDcrp_leaveDirty) {
        /* reset tables only */
        ZSTD_cwksp_clean_tables(ws);
    }

    /* opt parser space */
    if ((forWho == ZSTD_resetTarget_CCtx) && (cParams->strategy >= ZSTD_btopt)) {
        DEBUGLOG(4, "reserving optimal parser space");
        ms->opt.litFreq = (unsigned*)ZSTD_cwksp_reserve_aligned(ws, (1<<Litbits) * sizeof(unsigned));
        ms->opt.litLengthFreq = (unsigned*)ZSTD_cwksp_reserve_aligned(ws, (MaxLL+1) * sizeof(unsigned));
        ms->opt.matchLengthFreq = (unsigned*)ZSTD_cwksp_reserve_aligned(ws, (MaxML+1) * sizeof(unsigned));
        ms->opt.offCodeFreq = (unsigned*)ZSTD_cwksp_reserve_aligned(ws, (MaxOff+1) * sizeof(unsigned));
        ms->opt.matchTable = (ZSTD_match_t*)ZSTD_cwksp_reserve_aligned(ws, (ZSTD_OPT_NUM+1) * sizeof(ZSTD_match_t));
        ms->opt.priceTable = (ZSTD_optimal_t*)ZSTD_cwksp_reserve_aligned(ws, (ZSTD_OPT_NUM+1) * sizeof(ZSTD_optimal_t));
    }

    ms->cParams = *cParams;

    RETURN_ERROR_IF(ZSTD_cwksp_reserve_failed(ws), memory_allocation,
                    "failed a workspace allocation in ZSTD_reset_matchState");

    return 0;
}