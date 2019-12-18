#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int dictIDFlag; int checksumFlag; int nbWorkers; int minAdaptLevel; int maxAdaptLevel; scalar_t__ excludeCompressedFiles; int /*<<< orphan*/  literalCompressionMode; scalar_t__ testMode; scalar_t__ srcSizeHint; scalar_t__ targetCBlockSize; scalar_t__ streamSrcSize; void* ldmHashRateLog; void* ldmBucketSizeLog; scalar_t__ ldmMinMatch; scalar_t__ ldmHashLog; scalar_t__ ldmFlag; scalar_t__ rsyncable; scalar_t__ adaptiveMode; int /*<<< orphan*/  overlapLog; scalar_t__ blockSize; scalar_t__ memLimit; scalar_t__ removeSrcFile; int /*<<< orphan*/  sparseFileSupport; scalar_t__ overwrite; int /*<<< orphan*/  compressionType; } ;
typedef  TYPE_1__ FIO_prefs_t ;

/* Variables and functions */
 int /*<<< orphan*/  EXM_THROW (int,char*) ; 
 void* FIO_LDM_PARAM_NOTSET ; 
 int /*<<< orphan*/  FIO_OVERLAP_LOG_NOTSET ; 
 int /*<<< orphan*/  FIO_zstdCompression ; 
 int /*<<< orphan*/  ZSTD_SPARSE_DEFAULT ; 
 int /*<<< orphan*/  ZSTD_lcm_auto ; 
 scalar_t__ malloc (int) ; 

FIO_prefs_t* FIO_createPreferences(void)
{
    FIO_prefs_t* const ret = (FIO_prefs_t*)malloc(sizeof(FIO_prefs_t));
    if (!ret) EXM_THROW(21, "Allocation error : not enough memory");

    ret->compressionType = FIO_zstdCompression;
    ret->overwrite = 0;
    ret->sparseFileSupport = ZSTD_SPARSE_DEFAULT;
    ret->dictIDFlag = 1;
    ret->checksumFlag = 1;
    ret->removeSrcFile = 0;
    ret->memLimit = 0;
    ret->nbWorkers = 1;
    ret->blockSize = 0;
    ret->overlapLog = FIO_OVERLAP_LOG_NOTSET;
    ret->adaptiveMode = 0;
    ret->rsyncable = 0;
    ret->minAdaptLevel = -50;   /* initializing this value requires a constant, so ZSTD_minCLevel() doesn't work */
    ret->maxAdaptLevel = 22;   /* initializing this value requires a constant, so ZSTD_maxCLevel() doesn't work */
    ret->ldmFlag = 0;
    ret->ldmHashLog = 0;
    ret->ldmMinMatch = 0;
    ret->ldmBucketSizeLog = FIO_LDM_PARAM_NOTSET;
    ret->ldmHashRateLog = FIO_LDM_PARAM_NOTSET;
    ret->streamSrcSize = 0;
    ret->targetCBlockSize = 0;
    ret->srcSizeHint = 0;
    ret->testMode = 0;
    ret->literalCompressionMode = ZSTD_lcm_auto;
    ret->excludeCompressedFiles = 0;
    return ret;
}