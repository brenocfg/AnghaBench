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
typedef  int /*<<< orphan*/  ZSTDv06_DCtx ;

/* Variables and functions */
 int /*<<< orphan*/  ZSTDv06_checkContinuity (int /*<<< orphan*/ *,void*) ; 
 int /*<<< orphan*/  ZSTDv06_decompressBegin_usingDict (int /*<<< orphan*/ *,void const*,size_t) ; 
 size_t ZSTDv06_decompressFrame (int /*<<< orphan*/ *,void*,size_t,void const*,size_t) ; 

size_t ZSTDv06_decompress_usingDict(ZSTDv06_DCtx* dctx,
                                 void* dst, size_t dstCapacity,
                                 const void* src, size_t srcSize,
                                 const void* dict, size_t dictSize)
{
    ZSTDv06_decompressBegin_usingDict(dctx, dict, dictSize);
    ZSTDv06_checkContinuity(dctx, dst);
    return ZSTDv06_decompressFrame(dctx, dst, dstCapacity, src, srcSize);
}