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
struct TYPE_5__ {size_t size; size_t pos; void* dst; } ;
typedef  TYPE_1__ ZSTD_outBuffer ;
struct TYPE_6__ {size_t size; scalar_t__ pos; void const* src; } ;
typedef  TYPE_2__ ZSTD_inBuffer ;

/* Variables and functions */
 int /*<<< orphan*/  ZSTD_compressStream2 (int /*<<< orphan*/ ,TYPE_1__*,TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ZSTD_e_continue ; 
 int /*<<< orphan*/  ZSTD_e_end ; 
 int /*<<< orphan*/  g_cstream ; 

__attribute__((used)) static size_t
local_ZSTD_compress_generic_continue(const void* src, size_t srcSize,
                                     void* dst, size_t dstCapacity,
                                     void* payload)
{
    ZSTD_outBuffer buffOut;
    ZSTD_inBuffer buffIn;
    (void)payload;
    buffOut.dst = dst;
    buffOut.size = dstCapacity;
    buffOut.pos = 0;
    buffIn.src = src;
    buffIn.size = srcSize;
    buffIn.pos = 0;
    ZSTD_compressStream2(g_cstream, &buffOut, &buffIn, ZSTD_e_continue);
    ZSTD_compressStream2(g_cstream, &buffOut, &buffIn, ZSTD_e_end);
    return buffOut.pos;
}