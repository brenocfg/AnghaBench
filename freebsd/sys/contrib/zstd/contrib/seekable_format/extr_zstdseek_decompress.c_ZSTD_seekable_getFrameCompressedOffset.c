#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {unsigned int tableLen; TYPE_1__* entries; } ;
struct TYPE_7__ {TYPE_2__ seekTable; } ;
typedef  TYPE_3__ ZSTD_seekable ;
struct TYPE_5__ {unsigned long long cOffset; } ;

/* Variables and functions */
 unsigned long long ZSTD_SEEKABLE_FRAMEINDEX_TOOLARGE ; 

unsigned long long ZSTD_seekable_getFrameCompressedOffset(ZSTD_seekable* const zs, unsigned frameIndex)
{
    if (frameIndex >= zs->seekTable.tableLen) return ZSTD_SEEKABLE_FRAMEINDEX_TOOLARGE;
    return zs->seekTable.entries[frameIndex].cOffset;
}