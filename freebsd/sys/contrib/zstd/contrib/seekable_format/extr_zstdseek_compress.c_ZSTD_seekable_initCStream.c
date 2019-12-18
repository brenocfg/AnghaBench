#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int checksumFlag; scalar_t__ seekTableIndex; scalar_t__ seekTablePos; scalar_t__ size; } ;
struct TYPE_5__ {unsigned int maxFrameSize; int /*<<< orphan*/  cstream; scalar_t__ writingSeekTable; TYPE_1__ framelog; int /*<<< orphan*/  xxhState; scalar_t__ frameDSize; scalar_t__ frameCSize; } ;
typedef  TYPE_2__ ZSTD_seekable_CStream ;

/* Variables and functions */
 size_t ERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XXH64_reset (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 unsigned int ZSTD_SEEKABLE_MAX_FRAME_DECOMPRESSED_SIZE ; 
 size_t ZSTD_initCStream (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  frameParameter_unsupported ; 

size_t ZSTD_seekable_initCStream(ZSTD_seekable_CStream* zcs,
                                 int compressionLevel,
                                 int checksumFlag,
                                 unsigned maxFrameSize)
{
    zcs->framelog.size = 0;
    zcs->frameCSize = 0;
    zcs->frameDSize = 0;

    /* make sure maxFrameSize has a reasonable value */
    if (maxFrameSize > ZSTD_SEEKABLE_MAX_FRAME_DECOMPRESSED_SIZE) {
        return ERROR(frameParameter_unsupported);
    }

    zcs->maxFrameSize = maxFrameSize
                                ? maxFrameSize
                                : ZSTD_SEEKABLE_MAX_FRAME_DECOMPRESSED_SIZE;

    zcs->framelog.checksumFlag = checksumFlag;
    if (zcs->framelog.checksumFlag) {
        XXH64_reset(&zcs->xxhState, 0);
    }

    zcs->framelog.seekTablePos = 0;
    zcs->framelog.seekTableIndex = 0;
    zcs->writingSeekTable = 0;

    return ZSTD_initCStream(zcs->cstream, compressionLevel);
}