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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  FUZZ_dataProducer_t ;

/* Variables and functions */
 int /*<<< orphan*/  FUZZ_ASSERT (int) ; 
 int /*<<< orphan*/  FUZZ_ASSERT_MSG (int,char*) ; 
 int /*<<< orphan*/  FUZZ_ZASSERT (size_t const) ; 
 int /*<<< orphan*/ * FUZZ_dataProducer_create (int /*<<< orphan*/  const*,size_t) ; 
 int /*<<< orphan*/  FUZZ_dataProducer_free (int /*<<< orphan*/ *) ; 
 size_t FUZZ_dataProducer_reserveDataPrefix (int /*<<< orphan*/ *) ; 
 int ZSTD_compressBound (size_t) ; 
 int /*<<< orphan*/ * ZSTD_createCCtx () ; 
 int /*<<< orphan*/ * ZSTD_createDCtx () ; 
 size_t ZSTD_decompressDCtx (int /*<<< orphan*/ *,int /*<<< orphan*/ *,size_t,int /*<<< orphan*/ *,size_t const) ; 
 int /*<<< orphan*/  ZSTD_freeCCtx (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ZSTD_freeDCtx (int /*<<< orphan*/ *) ; 
 size_t bufSize ; 
 int /*<<< orphan*/ * cBuf ; 
 int /*<<< orphan*/ * cctx ; 
 size_t compress (int /*<<< orphan*/ *,size_t,int /*<<< orphan*/  const*,size_t,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * dctx ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 scalar_t__ malloc (size_t) ; 
 int /*<<< orphan*/  memcmp (int /*<<< orphan*/  const*,int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/ * rBuf ; 

int LLVMFuzzerTestOneInput(const uint8_t *src, size_t size)
{
    size_t neededBufSize;

    /* Give a random portion of src data to the producer, to use for
    parameter generation. The rest will be used for (de)compression */
    FUZZ_dataProducer_t *producer = FUZZ_dataProducer_create(src, size);
    size = FUZZ_dataProducer_reserveDataPrefix(producer);

    neededBufSize = ZSTD_compressBound(size) * 15;

    /* Allocate all buffers and contexts if not already allocated */
    if (neededBufSize > bufSize) {
        free(cBuf);
        free(rBuf);
        cBuf = (uint8_t*)malloc(neededBufSize);
        rBuf = (uint8_t*)malloc(neededBufSize);
        bufSize = neededBufSize;
        FUZZ_ASSERT(cBuf && rBuf);
    }
    if (!cctx) {
        cctx = ZSTD_createCCtx();
        FUZZ_ASSERT(cctx);
    }
    if (!dctx) {
        dctx = ZSTD_createDCtx();
        FUZZ_ASSERT(dctx);
    }

    {
        size_t const cSize = compress(cBuf, neededBufSize, src, size, producer);
        size_t const rSize =
            ZSTD_decompressDCtx(dctx, rBuf, neededBufSize, cBuf, cSize);
        FUZZ_ZASSERT(rSize);
        FUZZ_ASSERT_MSG(rSize == size, "Incorrect regenerated size");
        FUZZ_ASSERT_MSG(!memcmp(src, rBuf, size), "Corruption!");
    }

    FUZZ_dataProducer_free(producer);
#ifndef STATEFUL_FUZZING
    ZSTD_freeCCtx(cctx); cctx = NULL;
    ZSTD_freeDCtx(dctx); dctx = NULL;
#endif
    return 0;
}