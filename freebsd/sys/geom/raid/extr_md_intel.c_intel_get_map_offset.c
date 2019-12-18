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
struct intel_raid_map {scalar_t__ offset; scalar_t__ offset_hi; } ;
typedef  int off_t ;

/* Variables and functions */

__attribute__((used)) static off_t
intel_get_map_offset(struct intel_raid_map *mmap)
{
	off_t offset = (off_t)mmap->offset_hi << 32;

	offset += mmap->offset;
	return (offset);
}