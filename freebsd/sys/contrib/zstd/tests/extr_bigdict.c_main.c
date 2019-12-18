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
typedef  int /*<<< orphan*/  ZSTD_DCtx ;
typedef  int /*<<< orphan*/  ZSTD_CCtx ;

/* Variables and functions */
 int /*<<< orphan*/  RDG_genBuffer (char*,size_t const,double,double,int) ; 
 int /*<<< orphan*/  ZSTD_CCtx_setParameter (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ZSTD_DCtx_setParameter (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int ZSTD_btopt ; 
 int /*<<< orphan*/  ZSTD_c_chainLog ; 
 int /*<<< orphan*/  ZSTD_c_checksumFlag ; 
 int /*<<< orphan*/  ZSTD_c_hashLog ; 
 int /*<<< orphan*/  ZSTD_c_minMatch ; 
 int /*<<< orphan*/  ZSTD_c_nbWorkers ; 
 int /*<<< orphan*/  ZSTD_c_overlapLog ; 
 int /*<<< orphan*/  ZSTD_c_searchLog ; 
 int /*<<< orphan*/  ZSTD_c_strategy ; 
 int /*<<< orphan*/  ZSTD_c_targetLength ; 
 int /*<<< orphan*/  ZSTD_c_windowLog ; 
 size_t ZSTD_compressBound (size_t const) ; 
 int /*<<< orphan*/ * ZSTD_createCCtx () ; 
 int /*<<< orphan*/ * ZSTD_createDCtx () ; 
 int /*<<< orphan*/  ZSTD_d_windowLogMax ; 
 int /*<<< orphan*/  ZSTD_e_continue ; 
 int /*<<< orphan*/  ZSTD_e_end ; 
 int /*<<< orphan*/  ZSTD_freeCCtx (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ZSTD_freeDCtx (int /*<<< orphan*/ *) ; 
 scalar_t__ ZSTD_isError (int /*<<< orphan*/ ) ; 
 scalar_t__ compress (int /*<<< orphan*/ *,int /*<<< orphan*/ *,void*,size_t const,char*,size_t const,void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 void* malloc (size_t const) ; 
 int /*<<< orphan*/  stderr ; 

int main(int argc, const char** argv)
{
    ZSTD_CCtx* cctx = ZSTD_createCCtx();
    ZSTD_DCtx* dctx = ZSTD_createDCtx();
    const size_t dataSize = (size_t)1 << 30;
    const size_t outSize = ZSTD_compressBound(dataSize);
    const size_t bufferSize = (size_t)1 << 31;
    char* buffer = (char*)malloc(bufferSize);
    void* out = malloc(outSize);
    void* roundtrip = malloc(dataSize);
    (void)argc;
    (void)argv;

    if (!buffer || !out || !roundtrip || !cctx || !dctx) {
        fprintf(stderr, "Allocation failure\n");
        return 1;
    }

    if (ZSTD_isError(ZSTD_CCtx_setParameter(cctx, ZSTD_c_windowLog, 31)))
        return 1;
    if (ZSTD_isError(ZSTD_CCtx_setParameter(cctx, ZSTD_c_nbWorkers, 1)))
        return 1;
    if (ZSTD_isError(ZSTD_CCtx_setParameter(cctx, ZSTD_c_overlapLog, 9)))
        return 1;
    if (ZSTD_isError(ZSTD_CCtx_setParameter(cctx, ZSTD_c_checksumFlag, 1)))
        return 1;
    if (ZSTD_isError(ZSTD_CCtx_setParameter(cctx, ZSTD_c_strategy, ZSTD_btopt)))
        return 1;
    if (ZSTD_isError(ZSTD_CCtx_setParameter(cctx, ZSTD_c_targetLength, 7)))
        return 1;
    if (ZSTD_isError(ZSTD_CCtx_setParameter(cctx, ZSTD_c_minMatch, 7)))
        return 1;
    if (ZSTD_isError(ZSTD_CCtx_setParameter(cctx, ZSTD_c_searchLog, 1)))
        return 1;
    if (ZSTD_isError(ZSTD_CCtx_setParameter(cctx, ZSTD_c_hashLog, 10)))
        return 1;
    if (ZSTD_isError(ZSTD_CCtx_setParameter(cctx, ZSTD_c_chainLog, 10)))
        return 1;

    if (ZSTD_isError(ZSTD_DCtx_setParameter(dctx, ZSTD_d_windowLogMax, 31)))
        return 1;

    RDG_genBuffer(buffer, bufferSize, 1.0, 0.0, 0xbeefcafe);

    /* Compress 30 GB */
    {
        int i;
        for (i = 0; i < 10; ++i) {
            fprintf(stderr, "Compressing 1 GB\n");
            if (compress(cctx, dctx, out, outSize, buffer, dataSize, roundtrip, ZSTD_e_continue))
                return 1;
        }
    }
    fprintf(stderr, "Compressing 1 GB\n");
    if (compress(cctx, dctx, out, outSize, buffer, dataSize, roundtrip, ZSTD_e_end))
        return 1;

    fprintf(stderr, "Success!\n");

    free(roundtrip);
    free(out);
    free(buffer);
    ZSTD_freeDCtx(dctx);
    ZSTD_freeCCtx(cctx);
    return 0;
}