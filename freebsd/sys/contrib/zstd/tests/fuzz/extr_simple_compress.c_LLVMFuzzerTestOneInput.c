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
 int /*<<< orphan*/  FUZZ_ASSERT (void*) ; 
 int /*<<< orphan*/ * FUZZ_dataProducer_create (int /*<<< orphan*/  const*,size_t) ; 
 int /*<<< orphan*/  FUZZ_dataProducer_free (int /*<<< orphan*/ *) ; 
 int FUZZ_dataProducer_int32Range (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 size_t FUZZ_dataProducer_reserveDataPrefix (int /*<<< orphan*/ *) ; 
 size_t FUZZ_dataProducer_uint32Range (int /*<<< orphan*/ *,int /*<<< orphan*/ ,size_t const) ; 
 size_t ZSTD_compressBound (size_t) ; 
 int /*<<< orphan*/  ZSTD_compressCCtx (void*,void*,size_t const,int /*<<< orphan*/  const*,size_t,int const) ; 
 void* ZSTD_createCCtx () ; 
 int /*<<< orphan*/  ZSTD_freeCCtx (void*) ; 
 void* cctx ; 
 int /*<<< orphan*/  free (void*) ; 
 int /*<<< orphan*/  kMaxClevel ; 
 int /*<<< orphan*/  kMinClevel ; 
 void* malloc (size_t const) ; 

int LLVMFuzzerTestOneInput(const uint8_t *src, size_t size)
{
    /* Give a random portion of src data to the producer, to use for
    parameter generation. The rest will be used for (de)compression */
    FUZZ_dataProducer_t *producer = FUZZ_dataProducer_create(src, size);
    size = FUZZ_dataProducer_reserveDataPrefix(producer);

    size_t const maxSize = ZSTD_compressBound(size);
    size_t const bufSize = FUZZ_dataProducer_uint32Range(producer, 0, maxSize);

    int const cLevel = FUZZ_dataProducer_int32Range(producer, kMinClevel, kMaxClevel);

    if (!cctx) {
        cctx = ZSTD_createCCtx();
        FUZZ_ASSERT(cctx);
    }

    void *rBuf = malloc(bufSize);
    FUZZ_ASSERT(rBuf);
    ZSTD_compressCCtx(cctx, rBuf, bufSize, src, size, cLevel);
    free(rBuf);
    FUZZ_dataProducer_free(producer);
#ifndef STATEFUL_FUZZING
    ZSTD_freeCCtx(cctx); cctx = NULL;
#endif
    return 0;
}