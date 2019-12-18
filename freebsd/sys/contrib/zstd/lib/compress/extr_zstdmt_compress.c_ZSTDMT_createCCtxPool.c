#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ZSTD_customMem ;
typedef  int /*<<< orphan*/  ZSTD_CCtx ;
struct TYPE_5__ {int totalCCtx; int availCCtx; int /*<<< orphan*/ * cctx; int /*<<< orphan*/  cMem; int /*<<< orphan*/  poolMutex; } ;
typedef  TYPE_1__ ZSTDMT_CCtxPool ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUGLOG (int,char*,int) ; 
 int /*<<< orphan*/  ZSTDMT_freeCCtxPool (TYPE_1__* const) ; 
 scalar_t__ ZSTD_calloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ZSTD_createCCtx_advanced (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ZSTD_free (TYPE_1__* const,int /*<<< orphan*/ ) ; 
 scalar_t__ ZSTD_pthread_mutex_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  assert (int) ; 

__attribute__((used)) static ZSTDMT_CCtxPool* ZSTDMT_createCCtxPool(int nbWorkers,
                                              ZSTD_customMem cMem)
{
    ZSTDMT_CCtxPool* const cctxPool = (ZSTDMT_CCtxPool*) ZSTD_calloc(
        sizeof(ZSTDMT_CCtxPool) + (nbWorkers-1)*sizeof(ZSTD_CCtx*), cMem);
    assert(nbWorkers > 0);
    if (!cctxPool) return NULL;
    if (ZSTD_pthread_mutex_init(&cctxPool->poolMutex, NULL)) {
        ZSTD_free(cctxPool, cMem);
        return NULL;
    }
    cctxPool->cMem = cMem;
    cctxPool->totalCCtx = nbWorkers;
    cctxPool->availCCtx = 1;   /* at least one cctx for single-thread mode */
    cctxPool->cctx[0] = ZSTD_createCCtx_advanced(cMem);
    if (!cctxPool->cctx[0]) { ZSTDMT_freeCCtxPool(cctxPool); return NULL; }
    DEBUGLOG(3, "cctxPool created, with %u workers", nbWorkers);
    return cctxPool;
}