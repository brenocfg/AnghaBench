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
struct TYPE_3__ {scalar_t__ tableType; } ;
typedef  int /*<<< orphan*/  HUFv07_DTable ;
typedef  TYPE_1__ DTableDesc ;

/* Variables and functions */
 size_t HUFv07_decompress1X2_usingDTable_internal (void*,size_t,void const*,size_t,int /*<<< orphan*/  const*) ; 
 size_t HUFv07_decompress1X4_usingDTable_internal (void*,size_t,void const*,size_t,int /*<<< orphan*/  const*) ; 
 TYPE_1__ HUFv07_getDTableDesc (int /*<<< orphan*/  const*) ; 

size_t HUFv07_decompress1X_usingDTable(void* dst, size_t maxDstSize,
                                    const void* cSrc, size_t cSrcSize,
                                    const HUFv07_DTable* DTable)
{
    DTableDesc const dtd = HUFv07_getDTableDesc(DTable);
    return dtd.tableType ? HUFv07_decompress1X4_usingDTable_internal(dst, maxDstSize, cSrc, cSrcSize, DTable) :
                           HUFv07_decompress1X2_usingDTable_internal(dst, maxDstSize, cSrc, cSrcSize, DTable);
}