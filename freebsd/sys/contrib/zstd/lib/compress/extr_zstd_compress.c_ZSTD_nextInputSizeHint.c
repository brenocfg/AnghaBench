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
struct TYPE_3__ {size_t inBuffTarget; size_t inBuffPos; size_t blockSize; } ;
typedef  TYPE_1__ ZSTD_CCtx ;

/* Variables and functions */

__attribute__((used)) static size_t ZSTD_nextInputSizeHint(const ZSTD_CCtx* cctx)
{
    size_t hintInSize = cctx->inBuffTarget - cctx->inBuffPos;
    if (hintInSize==0) hintInSize = cctx->blockSize;
    return hintInSize;
}