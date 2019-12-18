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
 char* COMPRESSED ; 
 size_t COMPRESSED_SIZE ; 
 int /*<<< orphan*/  DISPLAY (char*,...) ; 
 int /*<<< orphan*/  EXPECTED ; 
 scalar_t__ ZSTD_decompressBound (char*,size_t) ; 
 size_t ZSTD_findFrameCompressedSize (char const*,size_t) ; 
 int /*<<< orphan*/  ZSTD_getErrorName (size_t) ; 
 scalar_t__ ZSTD_isError (size_t) ; 
 scalar_t__ strlen (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int testFrameDecoding(void)
{
    if (strlen(EXPECTED) > ZSTD_decompressBound(COMPRESSED, COMPRESSED_SIZE)) {
        DISPLAY("ERROR: ZSTD_decompressBound: decompressed bound too small\n");
        return 1;
    }
    {   const char* ip = COMPRESSED;
        size_t remainingSize = COMPRESSED_SIZE;
        while (1) {
            size_t frameSize = ZSTD_findFrameCompressedSize(ip, remainingSize);
            if (ZSTD_isError(frameSize)) {
                DISPLAY("ERROR: ZSTD_findFrameCompressedSize: %s\n", ZSTD_getErrorName(frameSize));
                return 1;
            }
            if (frameSize > remainingSize) {
                DISPLAY("ERROR: ZSTD_findFrameCompressedSize: expected frameSize to align with src buffer");
                return 1;
            }
            ip += frameSize;
            remainingSize -= frameSize;
            if (remainingSize == 0) break;
        }
    }
    DISPLAY("Frame Decoding OK\n");
    return 0;
}