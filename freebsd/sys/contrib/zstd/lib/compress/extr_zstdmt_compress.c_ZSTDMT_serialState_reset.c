#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_5__ ;
typedef  struct TYPE_18__   TYPE_4__ ;
typedef  struct TYPE_17__   TYPE_3__ ;
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;
typedef  struct TYPE_14__   TYPE_10__ ;

/* Type definitions */
struct TYPE_18__ {unsigned int hashLog; unsigned int bucketSizeLog; int hashRateLog; scalar_t__ enableLdm; int /*<<< orphan*/  minMatchLength; } ;
struct TYPE_15__ {scalar_t__ checksumFlag; } ;
struct TYPE_14__ {unsigned int windowLog; } ;
struct TYPE_19__ {scalar_t__ jobSize; TYPE_4__ ldmParams; int /*<<< orphan*/  customMem; TYPE_1__ fParams; TYPE_10__ cParams; } ;
struct TYPE_16__ {TYPE_4__* bucketOffsets; TYPE_4__* hashTable; int /*<<< orphan*/  window; int /*<<< orphan*/  hashPower; } ;
struct TYPE_17__ {TYPE_5__ params; TYPE_2__ ldmState; int /*<<< orphan*/  ldmWindow; int /*<<< orphan*/  xxhState; scalar_t__ nextJobID; } ;
typedef  TYPE_3__ serialState_t ;
typedef  TYPE_4__ ldmEntry_t ;
typedef  int /*<<< orphan*/  ZSTD_customMem ;
typedef  TYPE_5__ ZSTD_CCtx_params ;
typedef  int /*<<< orphan*/  ZSTDMT_seqPool ;
typedef  scalar_t__ U32 ;
typedef  TYPE_4__ BYTE ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUGLOG (int,char*,unsigned int) ; 
 int /*<<< orphan*/  XXH64_reset (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ZSTDMT_setNbSeq (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ZSTD_free (TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ZSTD_ldm_adjustParameters (TYPE_4__*,TYPE_10__*) ; 
 int /*<<< orphan*/  ZSTD_ldm_getMaxNbSeq (TYPE_4__,size_t) ; 
 scalar_t__ ZSTD_malloc (size_t const,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ZSTD_rollingHash_primePower (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ZSTD_window_clear (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  memset (TYPE_4__*,int /*<<< orphan*/ ,size_t const) ; 

__attribute__((used)) static int ZSTDMT_serialState_reset(serialState_t* serialState, ZSTDMT_seqPool* seqPool, ZSTD_CCtx_params params, size_t jobSize)
{
    /* Adjust parameters */
    if (params.ldmParams.enableLdm) {
        DEBUGLOG(4, "LDM window size = %u KB", (1U << params.cParams.windowLog) >> 10);
        ZSTD_ldm_adjustParameters(&params.ldmParams, &params.cParams);
        assert(params.ldmParams.hashLog >= params.ldmParams.bucketSizeLog);
        assert(params.ldmParams.hashRateLog < 32);
        serialState->ldmState.hashPower =
                ZSTD_rollingHash_primePower(params.ldmParams.minMatchLength);
    } else {
        memset(&params.ldmParams, 0, sizeof(params.ldmParams));
    }
    serialState->nextJobID = 0;
    if (params.fParams.checksumFlag)
        XXH64_reset(&serialState->xxhState, 0);
    if (params.ldmParams.enableLdm) {
        ZSTD_customMem cMem = params.customMem;
        unsigned const hashLog = params.ldmParams.hashLog;
        size_t const hashSize = ((size_t)1 << hashLog) * sizeof(ldmEntry_t);
        unsigned const bucketLog =
            params.ldmParams.hashLog - params.ldmParams.bucketSizeLog;
        size_t const bucketSize = (size_t)1 << bucketLog;
        unsigned const prevBucketLog =
            serialState->params.ldmParams.hashLog -
            serialState->params.ldmParams.bucketSizeLog;
        /* Size the seq pool tables */
        ZSTDMT_setNbSeq(seqPool, ZSTD_ldm_getMaxNbSeq(params.ldmParams, jobSize));
        /* Reset the window */
        ZSTD_window_clear(&serialState->ldmState.window);
        serialState->ldmWindow = serialState->ldmState.window;
        /* Resize tables and output space if necessary. */
        if (serialState->ldmState.hashTable == NULL || serialState->params.ldmParams.hashLog < hashLog) {
            ZSTD_free(serialState->ldmState.hashTable, cMem);
            serialState->ldmState.hashTable = (ldmEntry_t*)ZSTD_malloc(hashSize, cMem);
        }
        if (serialState->ldmState.bucketOffsets == NULL || prevBucketLog < bucketLog) {
            ZSTD_free(serialState->ldmState.bucketOffsets, cMem);
            serialState->ldmState.bucketOffsets = (BYTE*)ZSTD_malloc(bucketSize, cMem);
        }
        if (!serialState->ldmState.hashTable || !serialState->ldmState.bucketOffsets)
            return 1;
        /* Zero the tables */
        memset(serialState->ldmState.hashTable, 0, hashSize);
        memset(serialState->ldmState.bucketOffsets, 0, bucketSize);
    }
    serialState->params = params;
    serialState->params.jobSize = (U32)jobSize;
    return 0;
}