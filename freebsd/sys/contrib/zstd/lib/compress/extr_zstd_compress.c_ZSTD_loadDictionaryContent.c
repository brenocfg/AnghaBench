#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;
typedef  struct TYPE_13__   TYPE_12__ ;

/* Type definitions */
struct TYPE_16__ {int /*<<< orphan*/  const* const base; } ;
struct TYPE_14__ {TYPE_3__ window; void* nextToUpdate; int /*<<< orphan*/  cParams; void* loadedDictEnd; } ;
typedef  TYPE_1__ ZSTD_matchState_t ;
typedef  int /*<<< orphan*/  ZSTD_dictTableLoadMethod_e ;
typedef  int /*<<< orphan*/  ZSTD_cwksp ;
struct TYPE_13__ {int strategy; } ;
struct TYPE_15__ {TYPE_12__ cParams; scalar_t__ forceWindow; } ;
typedef  TYPE_2__ ZSTD_CCtx_params ;
typedef  void* U32 ;
typedef  int /*<<< orphan*/  BYTE ;

/* Variables and functions */
 size_t HASH_READ_SIZE ; 
 size_t MIN (size_t const,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ZSTD_CHUNKSIZE_MAX ; 
 int /*<<< orphan*/  ZSTD_assertEqualCParams (TYPE_12__,int /*<<< orphan*/ ) ; 
#define  ZSTD_btlazy2 136 
#define  ZSTD_btopt 135 
#define  ZSTD_btultra 134 
#define  ZSTD_btultra2 133 
#define  ZSTD_dfast 132 
#define  ZSTD_fast 131 
 int /*<<< orphan*/  ZSTD_fillDoubleHashTable (TYPE_1__*,int /*<<< orphan*/  const* const,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ZSTD_fillHashTable (TYPE_1__*,int /*<<< orphan*/  const* const,int /*<<< orphan*/ ) ; 
#define  ZSTD_greedy 130 
 int /*<<< orphan*/  ZSTD_insertAndFindFirstIndex (TYPE_1__*,int /*<<< orphan*/  const* const) ; 
#define  ZSTD_lazy 129 
#define  ZSTD_lazy2 128 
 int /*<<< orphan*/  ZSTD_overflowCorrectIfNeeded (TYPE_1__*,int /*<<< orphan*/ *,TYPE_2__ const*,int /*<<< orphan*/  const*,int /*<<< orphan*/  const* const) ; 
 int /*<<< orphan*/  ZSTD_updateTree (TYPE_1__*,int /*<<< orphan*/  const* const,int /*<<< orphan*/  const* const) ; 
 int /*<<< orphan*/  ZSTD_window_update (TYPE_3__*,void const*,size_t) ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 

__attribute__((used)) static size_t ZSTD_loadDictionaryContent(ZSTD_matchState_t* ms,
                                         ZSTD_cwksp* ws,
                                         ZSTD_CCtx_params const* params,
                                         const void* src, size_t srcSize,
                                         ZSTD_dictTableLoadMethod_e dtlm)
{
    const BYTE* ip = (const BYTE*) src;
    const BYTE* const iend = ip + srcSize;

    ZSTD_window_update(&ms->window, src, srcSize);
    ms->loadedDictEnd = params->forceWindow ? 0 : (U32)(iend - ms->window.base);

    /* Assert that we the ms params match the params we're being given */
    ZSTD_assertEqualCParams(params->cParams, ms->cParams);

    if (srcSize <= HASH_READ_SIZE) return 0;

    while (iend - ip > HASH_READ_SIZE) {
        size_t const remaining = (size_t)(iend - ip);
        size_t const chunk = MIN(remaining, ZSTD_CHUNKSIZE_MAX);
        const BYTE* const ichunk = ip + chunk;

        ZSTD_overflowCorrectIfNeeded(ms, ws, params, ip, ichunk);

        switch(params->cParams.strategy)
        {
        case ZSTD_fast:
            ZSTD_fillHashTable(ms, ichunk, dtlm);
            break;
        case ZSTD_dfast:
            ZSTD_fillDoubleHashTable(ms, ichunk, dtlm);
            break;

        case ZSTD_greedy:
        case ZSTD_lazy:
        case ZSTD_lazy2:
            if (chunk >= HASH_READ_SIZE)
                ZSTD_insertAndFindFirstIndex(ms, ichunk-HASH_READ_SIZE);
            break;

        case ZSTD_btlazy2:   /* we want the dictionary table fully sorted */
        case ZSTD_btopt:
        case ZSTD_btultra:
        case ZSTD_btultra2:
            if (chunk >= HASH_READ_SIZE)
                ZSTD_updateTree(ms, ichunk-HASH_READ_SIZE, ichunk);
            break;

        default:
            assert(0);  /* not possible : not a valid strategy id */
        }

        ip = ichunk;
    }

    ms->nextToUpdate = (U32)(iend - ms->window.base);
    return 0;
}