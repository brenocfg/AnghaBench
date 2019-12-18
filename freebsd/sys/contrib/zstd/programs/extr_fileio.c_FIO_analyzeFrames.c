#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  headerBuffer ;
struct TYPE_5__ {scalar_t__ compressedSize; int decompUnavailable; int usesCheck; int /*<<< orphan*/  numSkippableFrames; int /*<<< orphan*/  numActualFrames; int /*<<< orphan*/  windowSize; int /*<<< orphan*/  decompressedSize; } ;
typedef  TYPE_1__ fileInfo_t ;
struct TYPE_6__ {int /*<<< orphan*/  windowSize; } ;
typedef  TYPE_2__ ZSTD_frameHeader ;
typedef  scalar_t__ U64 ;
typedef  int U32 ;
typedef  int /*<<< orphan*/  InfoError ;
typedef  int /*<<< orphan*/  FILE ;
typedef  int BYTE ;

/* Variables and functions */
 int /*<<< orphan*/  ERROR_IF (int const,int /*<<< orphan*/ ,char*,...) ; 
 scalar_t__ LONG_SEEK (int /*<<< orphan*/ * const,long const,int /*<<< orphan*/ ) ; 
 scalar_t__ LONG_TELL (int /*<<< orphan*/ * const) ; 
 int MEM_readLE24 (int*) ; 
 int MEM_readLE32 (int*) ; 
 int /*<<< orphan*/  SEEK_CUR ; 
 scalar_t__ UTIL_FILESIZE_UNKNOWN ; 
 scalar_t__ const ZSTD_CONTENTSIZE_ERROR ; 
 scalar_t__ const ZSTD_CONTENTSIZE_UNKNOWN ; 
 int ZSTD_FRAMEHEADERSIZE_MAX ; 
 size_t const ZSTD_FRAMEHEADERSIZE_MIN (int /*<<< orphan*/ ) ; 
 int const ZSTD_MAGICNUMBER ; 
 int const ZSTD_MAGIC_SKIPPABLE_MASK ; 
 int const ZSTD_MAGIC_SKIPPABLE_START ; 
 int /*<<< orphan*/  ZSTD_f_zstd1 ; 
 size_t ZSTD_frameHeaderSize (int*,size_t const) ; 
 scalar_t__ ZSTD_getFrameContentSize (int*,size_t const) ; 
 scalar_t__ ZSTD_getFrameHeader (TYPE_2__*,int*,size_t const) ; 
 int ZSTD_isError (size_t const) ; 
 int feof (int /*<<< orphan*/ * const) ; 
 int fread (int*,int,int,int /*<<< orphan*/ * const) ; 
 scalar_t__ fseek (int /*<<< orphan*/ * const,long const,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  info_frame_error ; 
 int /*<<< orphan*/  info_not_zstd ; 
 int /*<<< orphan*/  info_success ; 
 int /*<<< orphan*/  info_truncated_input ; 

__attribute__((used)) static InfoError
FIO_analyzeFrames(fileInfo_t* info, FILE* const srcFile)
{
    /* begin analyzing frame */
    for ( ; ; ) {
        BYTE headerBuffer[ZSTD_FRAMEHEADERSIZE_MAX];
        size_t const numBytesRead = fread(headerBuffer, 1, sizeof(headerBuffer), srcFile);
        if (numBytesRead < ZSTD_FRAMEHEADERSIZE_MIN(ZSTD_f_zstd1)) {
            if ( feof(srcFile)
              && (numBytesRead == 0)
              && (info->compressedSize > 0)
              && (info->compressedSize != UTIL_FILESIZE_UNKNOWN) ) {
                unsigned long long file_position = (unsigned long long) LONG_TELL(srcFile);
                unsigned long long file_size = (unsigned long long) info->compressedSize;
                ERROR_IF(file_position != file_size, info_truncated_input,
                  "Error: seeked to position %llu, which is beyond file size of %llu\n",
                  file_position,
                  file_size);
                break;  /* correct end of file => success */
            }
            ERROR_IF(feof(srcFile), info_not_zstd, "Error: reached end of file with incomplete frame");
            ERROR_IF(1, info_frame_error, "Error: did not reach end of file but ran out of frames");
        }
        {   U32 const magicNumber = MEM_readLE32(headerBuffer);
            /* Zstandard frame */
            if (magicNumber == ZSTD_MAGICNUMBER) {
                ZSTD_frameHeader header;
                U64 const frameContentSize = ZSTD_getFrameContentSize(headerBuffer, numBytesRead);
                if ( frameContentSize == ZSTD_CONTENTSIZE_ERROR
                  || frameContentSize == ZSTD_CONTENTSIZE_UNKNOWN ) {
                    info->decompUnavailable = 1;
                } else {
                    info->decompressedSize += frameContentSize;
                }
                ERROR_IF(ZSTD_getFrameHeader(&header, headerBuffer, numBytesRead) != 0,
                        info_frame_error, "Error: could not decode frame header");
                info->windowSize = header.windowSize;
                /* move to the end of the frame header */
                {   size_t const headerSize = ZSTD_frameHeaderSize(headerBuffer, numBytesRead);
                    ERROR_IF(ZSTD_isError(headerSize), info_frame_error, "Error: could not determine frame header size");
                    ERROR_IF(fseek(srcFile, ((long)headerSize)-((long)numBytesRead), SEEK_CUR) != 0,
                            info_frame_error, "Error: could not move to end of frame header");
                }

                /* skip all blocks in the frame */
                {   int lastBlock = 0;
                    do {
                        BYTE blockHeaderBuffer[3];
                        ERROR_IF(fread(blockHeaderBuffer, 1, 3, srcFile) != 3,
                                info_frame_error, "Error while reading block header");
                        {   U32 const blockHeader = MEM_readLE24(blockHeaderBuffer);
                            U32 const blockTypeID = (blockHeader >> 1) & 3;
                            U32 const isRLE = (blockTypeID == 1);
                            U32 const isWrongBlock = (blockTypeID == 3);
                            long const blockSize = isRLE ? 1 : (long)(blockHeader >> 3);
                            ERROR_IF(isWrongBlock, info_frame_error, "Error: unsupported block type");
                            lastBlock = blockHeader & 1;
                            ERROR_IF(fseek(srcFile, blockSize, SEEK_CUR) != 0,
                                    info_frame_error, "Error: could not skip to end of block");
                        }
                    } while (lastBlock != 1);
                }

                /* check if checksum is used */
                {   BYTE const frameHeaderDescriptor = headerBuffer[4];
                    int const contentChecksumFlag = (frameHeaderDescriptor & (1 << 2)) >> 2;
                    if (contentChecksumFlag) {
                        info->usesCheck = 1;
                        ERROR_IF(fseek(srcFile, 4, SEEK_CUR) != 0,
                                info_frame_error, "Error: could not skip past checksum");
                }   }
                info->numActualFrames++;
            }
            /* Skippable frame */
            else if ((magicNumber & ZSTD_MAGIC_SKIPPABLE_MASK) == ZSTD_MAGIC_SKIPPABLE_START) {
                U32 const frameSize = MEM_readLE32(headerBuffer + 4);
                long const seek = (long)(8 + frameSize - numBytesRead);
                ERROR_IF(LONG_SEEK(srcFile, seek, SEEK_CUR) != 0,
                        info_frame_error, "Error: could not find end of skippable frame");
                info->numSkippableFrames++;
            }
            /* unknown content */
            else {
                return info_not_zstd;
            }
        }  /* magic number analysis */
    }  /* end analyzing frames */
    return info_success;
}