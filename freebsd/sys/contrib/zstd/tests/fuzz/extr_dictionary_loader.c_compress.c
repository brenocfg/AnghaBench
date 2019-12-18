#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  ZSTD_dictLoadMethod_e ;
typedef  int /*<<< orphan*/  ZSTD_dictContentType_e ;
typedef  int /*<<< orphan*/  ZSTD_CCtx ;

/* Variables and functions */
 int /*<<< orphan*/  FUZZ_ZASSERT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ZSTD_CCtx_loadDictionary_advanced (int /*<<< orphan*/ *,void const*,size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 size_t ZSTD_compress2 (int /*<<< orphan*/ *,void*,size_t,void const*,size_t) ; 
 int /*<<< orphan*/ * ZSTD_createCCtx () ; 
 int /*<<< orphan*/  ZSTD_freeCCtx (int /*<<< orphan*/ *) ; 

__attribute__((used)) static size_t compress(void* compressed, size_t compressedCapacity,
                       void const* source, size_t sourceSize,
                       void const* dict, size_t dictSize,
                       ZSTD_dictLoadMethod_e dictLoadMethod,
                       ZSTD_dictContentType_e dictContentType)
{
    ZSTD_CCtx* cctx = ZSTD_createCCtx();
    FUZZ_ZASSERT(ZSTD_CCtx_loadDictionary_advanced(
            cctx, dict, dictSize, dictLoadMethod, dictContentType));
    size_t const compressedSize = ZSTD_compress2(
            cctx, compressed, compressedCapacity, source, sourceSize);
    ZSTD_freeCCtx(cctx);
    return compressedSize;
}