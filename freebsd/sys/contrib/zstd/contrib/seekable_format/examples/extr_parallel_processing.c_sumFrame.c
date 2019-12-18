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
struct sum_job {int done; unsigned long long sum; int /*<<< orphan*/  frameNb; int /*<<< orphan*/  fname; } ;
typedef  int /*<<< orphan*/  ZSTD_seekable ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 char* ZSTD_getErrorName (size_t const) ; 
 scalar_t__ ZSTD_isError (size_t const) ; 
 int /*<<< orphan*/ * ZSTD_seekable_create () ; 
 size_t ZSTD_seekable_decompressFrame (int /*<<< orphan*/ * const,unsigned char*,size_t const,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ZSTD_seekable_free (int /*<<< orphan*/ * const) ; 
 size_t ZSTD_seekable_getFrameDecompressedSize (int /*<<< orphan*/ * const,int /*<<< orphan*/ ) ; 
 size_t ZSTD_seekable_initFile (int /*<<< orphan*/ * const,int /*<<< orphan*/ * const) ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ * const) ; 
 int /*<<< orphan*/ * fopen_orDie (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  free (unsigned char*) ; 
 unsigned char* malloc_orDie (size_t const) ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static void sumFrame(void* opaque)
{
    struct sum_job* job = (struct sum_job*)opaque;
    job->done = 0;

    FILE* const fin = fopen_orDie(job->fname, "rb");

    ZSTD_seekable* const seekable = ZSTD_seekable_create();
    if (seekable==NULL) { fprintf(stderr, "ZSTD_seekable_create() error \n"); exit(10); }

    size_t const initResult = ZSTD_seekable_initFile(seekable, fin);
    if (ZSTD_isError(initResult)) { fprintf(stderr, "ZSTD_seekable_init() error : %s \n", ZSTD_getErrorName(initResult)); exit(11); }

    size_t const frameSize = ZSTD_seekable_getFrameDecompressedSize(seekable, job->frameNb);
    unsigned char* data = malloc_orDie(frameSize);

    size_t result = ZSTD_seekable_decompressFrame(seekable, data, frameSize, job->frameNb);
    if (ZSTD_isError(result)) { fprintf(stderr, "ZSTD_seekable_decompressFrame() error : %s \n", ZSTD_getErrorName(result)); exit(12); }

    unsigned long long sum = 0;
    size_t i;
    for (i = 0; i < frameSize; i++) {
        sum += data[i];
    }
    job->sum = sum;
    job->done = 1;

    fclose(fin);
    ZSTD_seekable_free(seekable);
    free(data);
}