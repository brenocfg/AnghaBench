#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {unsigned long long pledgedSrcSize; int /*<<< orphan*/ * zbc; int /*<<< orphan*/  compressionLevel; } ;
typedef  TYPE_2__ ZWRAP_CCtx ;
struct TYPE_7__ {int /*<<< orphan*/  strategy; int /*<<< orphan*/  minMatch; int /*<<< orphan*/  searchLog; int /*<<< orphan*/  hashLog; int /*<<< orphan*/  chainLog; int /*<<< orphan*/  windowLog; } ;
struct TYPE_9__ {TYPE_1__ cParams; } ;
typedef  TYPE_3__ ZSTD_parameters ;

/* Variables and functions */
 int /*<<< orphan*/  LOG_WRAPPERC (char*,...) ; 
 TYPE_3__ ZSTD_getParams (int /*<<< orphan*/ ,unsigned long long,size_t) ; 
 size_t ZSTD_initCStream_advanced (int /*<<< orphan*/ *,void const*,size_t,TYPE_3__ const,unsigned long long) ; 
 scalar_t__ ZSTD_isError (size_t) ; 
 int Z_OK ; 
 int Z_STREAM_ERROR ; 

__attribute__((used)) static int ZWRAP_initializeCStream(ZWRAP_CCtx* zwc, const void* dict, size_t dictSize, unsigned long long pledgedSrcSize)
{
    LOG_WRAPPERC("- ZWRAP_initializeCStream=%p\n", zwc);
    if (zwc == NULL || zwc->zbc == NULL) return Z_STREAM_ERROR;

    if (!pledgedSrcSize) pledgedSrcSize = zwc->pledgedSrcSize;
    {   ZSTD_parameters const params = ZSTD_getParams(zwc->compressionLevel, pledgedSrcSize, dictSize);
        size_t initErr;
        LOG_WRAPPERC("pledgedSrcSize=%d windowLog=%d chainLog=%d hashLog=%d searchLog=%d minMatch=%d strategy=%d\n",
                    (int)pledgedSrcSize, params.cParams.windowLog, params.cParams.chainLog, params.cParams.hashLog, params.cParams.searchLog, params.cParams.minMatch, params.cParams.strategy);
        initErr = ZSTD_initCStream_advanced(zwc->zbc, dict, dictSize, params, pledgedSrcSize);
        if (ZSTD_isError(initErr)) return Z_STREAM_ERROR;
    }

    return Z_OK;
}