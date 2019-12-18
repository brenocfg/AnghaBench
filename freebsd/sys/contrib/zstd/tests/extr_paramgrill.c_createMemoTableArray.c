#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  varInds_t ;
struct TYPE_6__ {scalar_t__* vals; } ;
typedef  TYPE_1__ paramValues_t ;
struct TYPE_7__ {size_t tableLen; int /*<<< orphan*/ * table; int /*<<< orphan*/  tableType; int /*<<< orphan*/  varLen; int /*<<< orphan*/  varArray; } ;
typedef  TYPE_2__ memoTable_t ;
typedef  int ZSTD_strategy ;
typedef  scalar_t__ U32 ;
typedef  int /*<<< orphan*/  BYTE ;

/* Variables and functions */
 scalar_t__ PARAM_UNSET ; 
 size_t ZSTD_STRATEGY_MAX ; 
 int ZSTD_STRATEGY_MIN ; 
 scalar_t__ calloc (int,size_t) ; 
 int /*<<< orphan*/  directMap ; 
 int /*<<< orphan*/  freeMemoTableArray (TYPE_2__* const) ; 
 size_t memoTableLen (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  noMemo ; 
 int /*<<< orphan*/  sanitizeVarArray (int /*<<< orphan*/ ,size_t const,int /*<<< orphan*/  const* const,int) ; 
 size_t strt_ind ; 
 int /*<<< orphan*/  xxhashMap ; 

__attribute__((used)) static memoTable_t*
createMemoTableArray(const paramValues_t p,
                     const varInds_t* const varyParams,
                     const size_t varyLen,
                     const U32 memoTableLog)
{
    memoTable_t* const mtAll = (memoTable_t*)calloc(sizeof(memoTable_t),(ZSTD_STRATEGY_MAX + 1));
    ZSTD_strategy i, stratMin = ZSTD_STRATEGY_MIN, stratMax = ZSTD_STRATEGY_MAX;

    if(mtAll == NULL) {
        return NULL;
    }

    for(i = 1; i <= (int)ZSTD_STRATEGY_MAX; i++) {
        mtAll[i].varLen = sanitizeVarArray(mtAll[i].varArray, varyLen, varyParams, i);
    }

    /* no memoization */
    if(memoTableLog == 0) {
        for(i = 1; i <= (int)ZSTD_STRATEGY_MAX; i++) {
            mtAll[i].tableType = noMemo;
            mtAll[i].table = NULL;
            mtAll[i].tableLen = 0;
        }
        return mtAll;
    }


    if(p.vals[strt_ind] != PARAM_UNSET) {
        stratMin = p.vals[strt_ind];
        stratMax = p.vals[strt_ind];
    }


    for(i = stratMin; i <= stratMax; i++) {
        size_t mtl = memoTableLen(mtAll[i].varArray, mtAll[i].varLen);
        mtAll[i].tableType = directMap;

        if(memoTableLog != PARAM_UNSET && mtl > (1ULL << memoTableLog)) { /* use hash table */ /* provide some option to only use hash tables? */
            mtAll[i].tableType = xxhashMap;
            mtl = (1ULL << memoTableLog);
        }

        mtAll[i].table = (BYTE*)calloc(sizeof(BYTE), mtl);
        mtAll[i].tableLen = mtl;

        if(mtAll[i].table == NULL) {
            freeMemoTableArray(mtAll);
            return NULL;
        }
    }

    return mtAll;
}