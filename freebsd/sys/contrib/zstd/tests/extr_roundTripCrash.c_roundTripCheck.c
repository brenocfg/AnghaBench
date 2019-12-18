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

/* Variables and functions */
 size_t ZSTD_compressBound (size_t) ; 
 char* ZSTD_getErrorName (size_t const) ; 
 scalar_t__ ZSTD_isError (size_t const) ; 
 size_t cctxParamRoundTripTest (void*,size_t const,void*,size_t const,void const*,size_t) ; 
 size_t checkBuffers (void const*,void*,size_t) ; 
 int /*<<< orphan*/  crash (int) ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  free (void*) ; 
 void* malloc (size_t const) ; 
 size_t roundTripTest (void*,size_t const,void*,size_t const,void const*,size_t) ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static void roundTripCheck(const void* srcBuff, size_t srcBuffSize, int testCCtxParams)
{
    size_t const cBuffSize = ZSTD_compressBound(srcBuffSize);
    void* cBuff = malloc(cBuffSize);
    void* rBuff = malloc(cBuffSize);

    if (!cBuff || !rBuff) {
        fprintf(stderr, "not enough memory ! \n");
        exit (1);
    }

    {   size_t const result = testCCtxParams ?
                  cctxParamRoundTripTest(rBuff, cBuffSize, cBuff, cBuffSize, srcBuff, srcBuffSize)
                : roundTripTest(rBuff, cBuffSize, cBuff, cBuffSize, srcBuff, srcBuffSize);
        if (ZSTD_isError(result)) {
            fprintf(stderr, "roundTripTest error : %s \n", ZSTD_getErrorName(result));
            crash(1);
        }
        if (result != srcBuffSize) {
            fprintf(stderr, "Incorrect regenerated size : %u != %u\n", (unsigned)result, (unsigned)srcBuffSize);
            crash(1);
        }
        if (checkBuffers(srcBuff, rBuff, srcBuffSize) != srcBuffSize) {
            fprintf(stderr, "Silent decoding corruption !!!");
            crash(1);
        }
    }

    free(cBuff);
    free(rBuff);
}