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
typedef  int /*<<< orphan*/  ZSTD_parameters ;

/* Variables and functions */
 int /*<<< orphan*/  FUZZ_ASSERT (int) ; 
 int /*<<< orphan*/  FUZZ_ZASSERT (size_t) ; 
 size_t ZSTD_compressBegin_advanced (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/  const,size_t) ; 
 size_t ZSTD_compressBlock (int /*<<< orphan*/ ,void*,size_t,void const*,size_t) ; 
 int /*<<< orphan*/  ZSTD_decompressBegin (int /*<<< orphan*/ ) ; 
 size_t ZSTD_decompressBlock (int /*<<< orphan*/ ,void*,size_t,void*,size_t) ; 
 int /*<<< orphan*/  ZSTD_getParams (int,size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cctx ; 
 int /*<<< orphan*/  dctx ; 
 int /*<<< orphan*/  memcpy (void*,void const*,size_t) ; 

__attribute__((used)) static size_t roundTripTest(void *result, size_t resultCapacity,
                            void *compressed, size_t compressedCapacity,
                            const void *src, size_t srcSize,
                            int cLevel)
{
    ZSTD_parameters const params = ZSTD_getParams(cLevel, srcSize, 0);
    size_t ret = ZSTD_compressBegin_advanced(cctx, NULL, 0, params, srcSize);
    FUZZ_ZASSERT(ret);

    ret = ZSTD_compressBlock(cctx, compressed, compressedCapacity, src, srcSize);
    FUZZ_ZASSERT(ret);
    if (ret == 0) {
        FUZZ_ASSERT(resultCapacity >= srcSize);
        memcpy(result, src, srcSize);
        return srcSize;
    }
    ZSTD_decompressBegin(dctx);
    return ZSTD_decompressBlock(dctx, result, resultCapacity, compressed, ret);
}