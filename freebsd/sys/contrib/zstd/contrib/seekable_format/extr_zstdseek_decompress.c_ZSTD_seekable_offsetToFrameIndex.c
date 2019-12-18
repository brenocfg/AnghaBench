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
struct TYPE_6__ {size_t tableLen; TYPE_1__* entries; } ;
struct TYPE_7__ {TYPE_2__ seekTable; } ;
typedef  TYPE_3__ ZSTD_seekable ;
typedef  int U32 ;
struct TYPE_5__ {unsigned long long dOffset; } ;

/* Variables and functions */
 size_t UINT_MAX ; 
 int /*<<< orphan*/  assert (int) ; 

unsigned ZSTD_seekable_offsetToFrameIndex(ZSTD_seekable* const zs, unsigned long long pos)
{
    U32 lo = 0;
    U32 hi = (U32)zs->seekTable.tableLen;
    assert(zs->seekTable.tableLen <= UINT_MAX);

    if (pos >= zs->seekTable.entries[zs->seekTable.tableLen].dOffset) {
        return (U32)zs->seekTable.tableLen;
    }

    while (lo + 1 < hi) {
        U32 const mid = lo + ((hi - lo) >> 1);
        if (zs->seekTable.entries[mid].dOffset <= pos) {
            lo = mid;
        } else {
            hi = mid;
        }
    }
    return lo;
}