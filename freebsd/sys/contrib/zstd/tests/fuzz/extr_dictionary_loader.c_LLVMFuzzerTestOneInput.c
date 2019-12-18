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
typedef  unsigned int ZSTD_dictLoadMethod_e ;
typedef  scalar_t__ ZSTD_dictContentType_e ;
typedef  int /*<<< orphan*/  FUZZ_dataProducer_t ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUGLOG (int,char*,unsigned int const) ; 
 int /*<<< orphan*/  FUZZ_ASSERT (void* const) ; 
 int /*<<< orphan*/  FUZZ_ASSERT_MSG (int,char*) ; 
 int /*<<< orphan*/ * FUZZ_dataProducer_create (int /*<<< orphan*/  const*,size_t) ; 
 int /*<<< orphan*/  FUZZ_dataProducer_free (int /*<<< orphan*/ *) ; 
 size_t FUZZ_dataProducer_remainingBytes (int /*<<< orphan*/ *) ; 
 void* FUZZ_dataProducer_uint32Range (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 size_t ZSTD_compressBound (size_t) ; 
 scalar_t__ const ZSTD_dct_rawContent ; 
 scalar_t__ ZSTD_isError (size_t const) ; 
 size_t compress (void* const,size_t const,int /*<<< orphan*/  const*,size_t,int /*<<< orphan*/  const*,size_t,unsigned int const,scalar_t__ const) ; 
 size_t decompress (void* const,size_t,void* const,size_t const,int /*<<< orphan*/  const*,size_t,unsigned int const,scalar_t__ const) ; 
 int /*<<< orphan*/  free (void* const) ; 
 void* malloc (size_t const) ; 
 int /*<<< orphan*/  memcmp (int /*<<< orphan*/  const*,void* const,size_t) ; 

int LLVMFuzzerTestOneInput(const uint8_t *src, size_t size)
{
    FUZZ_dataProducer_t *producer = FUZZ_dataProducer_create(src, size);
    ZSTD_dictLoadMethod_e const dlm =
    size = FUZZ_dataProducer_uint32Range(producer, 0, 1);
    ZSTD_dictContentType_e const dct =
            FUZZ_dataProducer_uint32Range(producer, 0, 2);
    size = FUZZ_dataProducer_remainingBytes(producer);

    DEBUGLOG(2, "Dict load method %d", dlm);
    DEBUGLOG(2, "Dict content type %d", dct);
    DEBUGLOG(2, "Dict size %u", (unsigned)size);

    void* const rBuf = malloc(size);
    FUZZ_ASSERT(rBuf);
    size_t const cBufSize = ZSTD_compressBound(size);
    void* const cBuf = malloc(cBufSize);
    FUZZ_ASSERT(cBuf);

    size_t const cSize =
            compress(cBuf, cBufSize, src, size, src, size, dlm, dct);
    /* compression failing is okay */
    if (ZSTD_isError(cSize)) {
      FUZZ_ASSERT_MSG(dct != ZSTD_dct_rawContent, "Raw must always succeed!");
      goto out;
    }
    size_t const rSize =
            decompress(rBuf, size, cBuf, cSize, src, size, dlm, dct);
    FUZZ_ASSERT_MSG(rSize == size, "Incorrect regenerated size");
    FUZZ_ASSERT_MSG(!memcmp(src, rBuf, size), "Corruption!");

out:
    free(cBuf);
    free(rBuf);
    FUZZ_dataProducer_free(producer);
    return 0;
}