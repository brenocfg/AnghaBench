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
typedef  int /*<<< orphan*/  blockProperties_t ;
typedef  scalar_t__ U32 ;
typedef  int /*<<< orphan*/  BYTE ;

/* Variables and functions */
 size_t BLOCKSIZE ; 
 size_t ERROR (int /*<<< orphan*/ ) ; 
 size_t ZSTD_blockHeaderSize ; 
 int /*<<< orphan*/  ZSTD_errorFrameSizeInfoLegacy (size_t*,unsigned long long*,size_t) ; 
 size_t ZSTD_frameHeaderSize ; 
 scalar_t__ ZSTD_magicNumber ; 
 scalar_t__ ZSTD_readBE32 (void const*) ; 
 size_t ZSTDv01_getcBlockSize (int /*<<< orphan*/  const*,size_t,int /*<<< orphan*/ *) ; 
 scalar_t__ ZSTDv01_isError (size_t) ; 
 int /*<<< orphan*/  prefix_unknown ; 
 int /*<<< orphan*/  srcSize_wrong ; 

void ZSTDv01_findFrameSizeInfoLegacy(const void *src, size_t srcSize, size_t* cSize, unsigned long long* dBound)
{
    const BYTE* ip = (const BYTE*)src;
    size_t remainingSize = srcSize;
    size_t nbBlocks = 0;
    U32 magicNumber;
    blockProperties_t blockProperties;

    /* Frame Header */
    if (srcSize < ZSTD_frameHeaderSize+ZSTD_blockHeaderSize) {
        ZSTD_errorFrameSizeInfoLegacy(cSize, dBound, ERROR(srcSize_wrong));
        return;
    }
    magicNumber = ZSTD_readBE32(src);
    if (magicNumber != ZSTD_magicNumber) {
        ZSTD_errorFrameSizeInfoLegacy(cSize, dBound, ERROR(prefix_unknown));
        return;
    }
    ip += ZSTD_frameHeaderSize; remainingSize -= ZSTD_frameHeaderSize;

    /* Loop on each block */
    while (1)
    {
        size_t blockSize = ZSTDv01_getcBlockSize(ip, remainingSize, &blockProperties);
        if (ZSTDv01_isError(blockSize)) {
            ZSTD_errorFrameSizeInfoLegacy(cSize, dBound, blockSize);
            return;
        }

        ip += ZSTD_blockHeaderSize;
        remainingSize -= ZSTD_blockHeaderSize;
        if (blockSize > remainingSize) {
            ZSTD_errorFrameSizeInfoLegacy(cSize, dBound, ERROR(srcSize_wrong));
            return;
        }

        if (blockSize == 0) break;   /* bt_end */

        ip += blockSize;
        remainingSize -= blockSize;
        nbBlocks++;
    }

    *cSize = ip - (const BYTE*)src;
    *dBound = nbBlocks * BLOCKSIZE;
}