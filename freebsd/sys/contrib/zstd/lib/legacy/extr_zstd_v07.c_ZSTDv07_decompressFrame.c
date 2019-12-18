#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int blockType; int /*<<< orphan*/  origSize; } ;
typedef  TYPE_2__ blockProperties_t ;
struct TYPE_8__ {scalar_t__ checksumFlag; } ;
struct TYPE_10__ {int /*<<< orphan*/  xxhState; TYPE_1__ fParams; } ;
typedef  TYPE_3__ ZSTDv07_DCtx ;
typedef  int /*<<< orphan*/  BYTE ;

/* Variables and functions */
 size_t ERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GENERIC ; 
 int /*<<< orphan*/  XXH64_update (int /*<<< orphan*/ *,int /*<<< orphan*/ *,size_t) ; 
 size_t ZSTDv07_blockHeaderSize ; 
 size_t ZSTDv07_copyRawBlock (int /*<<< orphan*/ *,int,int /*<<< orphan*/  const*,size_t const) ; 
 scalar_t__ ZSTDv07_decodeFrameHeader (TYPE_3__*,void const*,size_t const) ; 
 size_t ZSTDv07_decompressBlock_internal (TYPE_3__*,int /*<<< orphan*/ *,int,int /*<<< orphan*/  const*,size_t const) ; 
 size_t ZSTDv07_frameHeaderSize (void const*,size_t) ; 
 size_t ZSTDv07_frameHeaderSize_min ; 
 size_t ZSTDv07_generateNxBytes (int /*<<< orphan*/ *,int,int /*<<< orphan*/  const,int /*<<< orphan*/ ) ; 
 size_t ZSTDv07_getcBlockSize (int /*<<< orphan*/  const*,int,TYPE_2__*) ; 
 scalar_t__ ZSTDv07_isError (size_t const) ; 
#define  bt_compressed 131 
#define  bt_end 130 
#define  bt_raw 129 
#define  bt_rle 128 
 int /*<<< orphan*/  corruption_detected ; 
 int /*<<< orphan*/  srcSize_wrong ; 

__attribute__((used)) static size_t ZSTDv07_decompressFrame(ZSTDv07_DCtx* dctx,
                                 void* dst, size_t dstCapacity,
                                 const void* src, size_t srcSize)
{
    const BYTE* ip = (const BYTE*)src;
    const BYTE* const iend = ip + srcSize;
    BYTE* const ostart = (BYTE* const)dst;
    BYTE* const oend = ostart + dstCapacity;
    BYTE* op = ostart;
    size_t remainingSize = srcSize;

    /* check */
    if (srcSize < ZSTDv07_frameHeaderSize_min+ZSTDv07_blockHeaderSize) return ERROR(srcSize_wrong);

    /* Frame Header */
    {   size_t const frameHeaderSize = ZSTDv07_frameHeaderSize(src, ZSTDv07_frameHeaderSize_min);
        if (ZSTDv07_isError(frameHeaderSize)) return frameHeaderSize;
        if (srcSize < frameHeaderSize+ZSTDv07_blockHeaderSize) return ERROR(srcSize_wrong);
        if (ZSTDv07_decodeFrameHeader(dctx, src, frameHeaderSize)) return ERROR(corruption_detected);
        ip += frameHeaderSize; remainingSize -= frameHeaderSize;
    }

    /* Loop on each block */
    while (1) {
        size_t decodedSize;
        blockProperties_t blockProperties;
        size_t const cBlockSize = ZSTDv07_getcBlockSize(ip, iend-ip, &blockProperties);
        if (ZSTDv07_isError(cBlockSize)) return cBlockSize;

        ip += ZSTDv07_blockHeaderSize;
        remainingSize -= ZSTDv07_blockHeaderSize;
        if (cBlockSize > remainingSize) return ERROR(srcSize_wrong);

        switch(blockProperties.blockType)
        {
        case bt_compressed:
            decodedSize = ZSTDv07_decompressBlock_internal(dctx, op, oend-op, ip, cBlockSize);
            break;
        case bt_raw :
            decodedSize = ZSTDv07_copyRawBlock(op, oend-op, ip, cBlockSize);
            break;
        case bt_rle :
            decodedSize = ZSTDv07_generateNxBytes(op, oend-op, *ip, blockProperties.origSize);
            break;
        case bt_end :
            /* end of frame */
            if (remainingSize) return ERROR(srcSize_wrong);
            decodedSize = 0;
            break;
        default:
            return ERROR(GENERIC);   /* impossible */
        }
        if (blockProperties.blockType == bt_end) break;   /* bt_end */

        if (ZSTDv07_isError(decodedSize)) return decodedSize;
        if (dctx->fParams.checksumFlag) XXH64_update(&dctx->xxhState, op, decodedSize);
        op += decodedSize;
        ip += cBlockSize;
        remainingSize -= cBlockSize;
    }

    return op-ostart;
}