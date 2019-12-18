#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  unsigned int U64 ;
typedef  unsigned int U32 ;
struct TYPE_6__ {size_t const* samplesSizes; unsigned int nbSamples; unsigned int nbTrainSamples; unsigned int nbTestSamples; size_t nbDmers; unsigned int d; unsigned int f; size_t* offsets; unsigned int* freqs; int /*<<< orphan*/  accelParams; int /*<<< orphan*/ * samples; } ;
typedef  TYPE_1__ FASTCOVER_ctx_t ;
typedef  int /*<<< orphan*/  FASTCOVER_accel_t ;
typedef  int /*<<< orphan*/  BYTE ;

/* Variables and functions */
 size_t const COVER_sum (size_t const*,unsigned int const) ; 
 int /*<<< orphan*/  DISPLAYLEVEL (int,char*,...) ; 
 size_t ERROR (int /*<<< orphan*/ ) ; 
 int FASTCOVER_MAX_SAMPLES_SIZE ; 
 int /*<<< orphan*/  FASTCOVER_computeFrequency (unsigned int*,TYPE_1__*) ; 
 int /*<<< orphan*/  FASTCOVER_ctx_destroy (TYPE_1__*) ; 
 size_t const MAX (unsigned int,int) ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ calloc (unsigned int,int) ; 
 int /*<<< orphan*/  memory_allocation ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  srcSize_wrong ; 

__attribute__((used)) static size_t
FASTCOVER_ctx_init(FASTCOVER_ctx_t* ctx,
                   const void* samplesBuffer,
                   const size_t* samplesSizes, unsigned nbSamples,
                   unsigned d, double splitPoint, unsigned f,
                   FASTCOVER_accel_t accelParams)
{
    const BYTE* const samples = (const BYTE*)samplesBuffer;
    const size_t totalSamplesSize = COVER_sum(samplesSizes, nbSamples);
    /* Split samples into testing and training sets */
    const unsigned nbTrainSamples = splitPoint < 1.0 ? (unsigned)((double)nbSamples * splitPoint) : nbSamples;
    const unsigned nbTestSamples = splitPoint < 1.0 ? nbSamples - nbTrainSamples : nbSamples;
    const size_t trainingSamplesSize = splitPoint < 1.0 ? COVER_sum(samplesSizes, nbTrainSamples) : totalSamplesSize;
    const size_t testSamplesSize = splitPoint < 1.0 ? COVER_sum(samplesSizes + nbTrainSamples, nbTestSamples) : totalSamplesSize;

    /* Checks */
    if (totalSamplesSize < MAX(d, sizeof(U64)) ||
        totalSamplesSize >= (size_t)FASTCOVER_MAX_SAMPLES_SIZE) {
        DISPLAYLEVEL(1, "Total samples size is too large (%u MB), maximum size is %u MB\n",
                    (unsigned)(totalSamplesSize >> 20), (FASTCOVER_MAX_SAMPLES_SIZE >> 20));
        return ERROR(srcSize_wrong);
    }

    /* Check if there are at least 5 training samples */
    if (nbTrainSamples < 5) {
        DISPLAYLEVEL(1, "Total number of training samples is %u and is invalid\n", nbTrainSamples);
        return ERROR(srcSize_wrong);
    }

    /* Check if there's testing sample */
    if (nbTestSamples < 1) {
        DISPLAYLEVEL(1, "Total number of testing samples is %u and is invalid.\n", nbTestSamples);
        return ERROR(srcSize_wrong);
    }

    /* Zero the context */
    memset(ctx, 0, sizeof(*ctx));
    DISPLAYLEVEL(2, "Training on %u samples of total size %u\n", nbTrainSamples,
                    (unsigned)trainingSamplesSize);
    DISPLAYLEVEL(2, "Testing on %u samples of total size %u\n", nbTestSamples,
                    (unsigned)testSamplesSize);

    ctx->samples = samples;
    ctx->samplesSizes = samplesSizes;
    ctx->nbSamples = nbSamples;
    ctx->nbTrainSamples = nbTrainSamples;
    ctx->nbTestSamples = nbTestSamples;
    ctx->nbDmers = trainingSamplesSize - MAX(d, sizeof(U64)) + 1;
    ctx->d = d;
    ctx->f = f;
    ctx->accelParams = accelParams;

    /* The offsets of each file */
    ctx->offsets = (size_t*)calloc((nbSamples + 1), sizeof(size_t));
    if (ctx->offsets == NULL) {
        DISPLAYLEVEL(1, "Failed to allocate scratch buffers \n");
        FASTCOVER_ctx_destroy(ctx);
        return ERROR(memory_allocation);
    }

    /* Fill offsets from the samplesSizes */
    {   U32 i;
        ctx->offsets[0] = 0;
        assert(nbSamples >= 5);
        for (i = 1; i <= nbSamples; ++i) {
            ctx->offsets[i] = ctx->offsets[i - 1] + samplesSizes[i - 1];
        }
    }

    /* Initialize frequency array of size 2^f */
    ctx->freqs = (U32*)calloc(((U64)1 << f), sizeof(U32));
    if (ctx->freqs == NULL) {
        DISPLAYLEVEL(1, "Failed to allocate frequency table \n");
        FASTCOVER_ctx_destroy(ctx);
        return ERROR(memory_allocation);
    }

    DISPLAYLEVEL(2, "Computing frequencies\n");
    FASTCOVER_computeFrequency(ctx->freqs, ctx);

    return 0;
}