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
struct intel_raid_map {int offset; int offset_hi; } ;
typedef  int off_t ;

/* Variables and functions */

__attribute__((used)) static void
intel_set_map_offset(struct intel_raid_map *mmap, off_t offset)
{

	mmap->offset = offset & 0xffffffff;
	mmap->offset_hi = offset >> 32;
}