#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  srcStart; scalar_t__ dataStart; scalar_t__ data; } ;
typedef  TYPE_1__ frame_t ;
struct TYPE_8__ {size_t pos; int /*<<< orphan*/  dst; scalar_t__ size; } ;
typedef  TYPE_2__ ZSTD_outBuffer ;
struct TYPE_9__ {int size; scalar_t__ pos; scalar_t__ src; } ;
typedef  TYPE_3__ ZSTD_inBuffer ;
typedef  int /*<<< orphan*/  ZSTD_DStream ;
typedef  int /*<<< orphan*/  BYTE ;

/* Variables and functions */
 int /*<<< orphan*/  DECOMPRESSED_BUFFER ; 
 size_t ERROR (int /*<<< orphan*/ ) ; 
 scalar_t__ MAX_DECOMPRESSED_SIZE ; 
 scalar_t__ MIN (scalar_t__,scalar_t__) ; 
 scalar_t__ ZSTD_DStreamOutSize () ; 
 int /*<<< orphan*/ * ZSTD_createDStream () ; 
 size_t ZSTD_decompressStream (int /*<<< orphan*/ *,TYPE_2__*,TYPE_3__*) ; 
 int /*<<< orphan*/  ZSTD_freeDStream (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ZSTD_initDStream (int /*<<< orphan*/ *) ; 
 scalar_t__ ZSTD_isError (size_t) ; 
 int /*<<< orphan*/  corruption_detected ; 
 scalar_t__ memcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  memory_allocation ; 

__attribute__((used)) static size_t testDecodeStreaming(frame_t* fr)
{
    /* test decoding the generated data with the streaming API */
    ZSTD_DStream* zd = ZSTD_createDStream();
    ZSTD_inBuffer in;
    ZSTD_outBuffer out;
    size_t ret;

    if (!zd) return ERROR(memory_allocation);

    in.src = fr->dataStart;
    in.pos = 0;
    in.size = (BYTE*)fr->data - (BYTE*)fr->dataStart;

    out.dst = DECOMPRESSED_BUFFER;
    out.pos = 0;
    out.size = ZSTD_DStreamOutSize();

    ZSTD_initDStream(zd);
    while (1) {
        ret = ZSTD_decompressStream(zd, &out, &in);
        if (ZSTD_isError(ret)) goto cleanup; /* error */
        if (ret == 0) break; /* frame is done */

        /* force decoding to be done in chunks */
        out.size += MIN(ZSTD_DStreamOutSize(), MAX_DECOMPRESSED_SIZE - out.size);
    }

    ret = out.pos;

    if (memcmp(out.dst, fr->srcStart, out.pos) != 0) {
        return ERROR(corruption_detected);
    }

cleanup:
    ZSTD_freeDStream(zd);
    return ret;
}