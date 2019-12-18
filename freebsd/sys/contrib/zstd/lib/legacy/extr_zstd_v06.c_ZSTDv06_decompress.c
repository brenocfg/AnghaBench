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
 size_t ERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * ZSTDv06_createDCtx () ; 
 size_t ZSTDv06_decompressDCtx (int /*<<< orphan*/ *,void*,size_t,void const*,size_t) ; 
 int /*<<< orphan*/  ZSTDv06_freeDCtx (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memory_allocation ; 

size_t ZSTDv06_decompress(void* dst, size_t dstCapacity, const void* src, size_t srcSize)
{
#if defined(ZSTDv06_HEAPMODE) && (ZSTDv06_HEAPMODE==1)
    size_t regenSize;
    ZSTDv06_DCtx* dctx = ZSTDv06_createDCtx();
    if (dctx==NULL) return ERROR(memory_allocation);
    regenSize = ZSTDv06_decompressDCtx(dctx, dst, dstCapacity, src, srcSize);
    ZSTDv06_freeDCtx(dctx);
    return regenSize;
#else   /* stack mode */
    ZSTDv06_DCtx dctx;
    return ZSTDv06_decompressDCtx(&dctx, dst, dstCapacity, src, srcSize);
#endif
}