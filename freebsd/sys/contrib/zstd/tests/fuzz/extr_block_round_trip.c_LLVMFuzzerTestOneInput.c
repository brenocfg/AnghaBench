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
 int FUZZ_dataProducer_int32Range (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 size_t FUZZ_dataProducer_reserveDataPrefix (int /*<<< orphan*/ *) ; 
 size_t ZSTD_BLOCKSIZE_MAX ; 
 int /*<<< orphan*/ * ZSTD_createCCtx () ; 
 int /*<<< orphan*/ * ZSTD_createDCtx () ; 
 int /*<<< orphan*/  ZSTD_freeCCtx (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ZSTD_freeDCtx (int /*<<< orphan*/ *) ; 
 size_t bufSize ; 
 scalar_t__ cBuf ; 
 int /*<<< orphan*/ * cctx ; 
 int /*<<< orphan*/ * dctx ; 
 int /*<<< orphan*/  free (scalar_t__) ; 
 int /*<<< orphan*/  kMaxClevel ; 
 int /*<<< orphan*/  kMinClevel ; 
 scalar_t__ malloc (size_t) ; 
 int /*<<< orphan*/  memcmp (int /*<<< orphan*/  const*,scalar_t__,size_t) ; 
 scalar_t__ rBuf ; 
 size_t roundTripTest (scalar_t__,size_t,scalar_t__,size_t,int /*<<< orphan*/  const*,size_t,int const) ; 

int LLVMFuzzerTestOneInput(const uint8_t *src, size_t size)
{
    /* Give a random portion of src data to the producer, to use for
    parameter generation. The rest will be used for (de)compression */
    FUZZ_dataProducer_t *producer = FUZZ_dataProducer_create(src, size);
    size = FUZZ_dataProducer_reserveDataPrefix(producer);

    int const cLevel = FUZZ_dataProducer_int32Range(producer, kMinClevel, kMaxClevel);

    size_t neededBufSize = size;
    if (size > ZSTD_BLOCKSIZE_MAX)
        size = ZSTD_BLOCKSIZE_MAX;

    /* Allocate all buffers and contexts if not already allocated */
    if (neededBufSize > bufSize || !cBuf || !rBuf) {
        free(cBuf);
        free(rBuf);
        cBuf = malloc(neededBufSize);
        rBuf = malloc(neededBufSize);
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
        size_t const result =
            roundTripTest(rBuf, neededBufSize, cBuf, neededBufSize, src, size,
              cLevel);
        FUZZ_ZASSERT(result);
        FUZZ_ASSERT_MSG(result == size, "Incorrect regenerated size");
        FUZZ_ASSERT_MSG(!memcmp(src, rBuf, size), "Corruption!");
    }
    FUZZ_dataProducer_free(producer);
#ifndef STATEFUL_FUZZING
    ZSTD_freeCCtx(cctx); cctx = NULL;
    ZSTD_freeDCtx(dctx); dctx = NULL;
#endif
    return 0;
}