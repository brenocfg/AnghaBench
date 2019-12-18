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
struct TYPE_3__ {int /*<<< orphan*/  zc; scalar_t__ outEnd; scalar_t__ outStart; scalar_t__ inPos; scalar_t__ hPos; int /*<<< orphan*/  stage; } ;
typedef  TYPE_1__ ZBUFFv05_DCtx ;

/* Variables and functions */
 int /*<<< orphan*/  ZBUFFv05ds_readHeader ; 
 size_t ZSTDv05_decompressBegin_usingDict (int /*<<< orphan*/ ,void const*,size_t) ; 

size_t ZBUFFv05_decompressInitDictionary(ZBUFFv05_DCtx* zbc, const void* dict, size_t dictSize)
{
    zbc->stage = ZBUFFv05ds_readHeader;
    zbc->hPos = zbc->inPos = zbc->outStart = zbc->outEnd = 0;
    return ZSTDv05_decompressBegin_usingDict(zbc->zc, dict, dictSize);
}