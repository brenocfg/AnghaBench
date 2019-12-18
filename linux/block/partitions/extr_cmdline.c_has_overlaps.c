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
typedef  scalar_t__ sector_t ;

/* Variables and functions */

__attribute__((used)) static bool has_overlaps(sector_t from, sector_t size,
			 sector_t from2, sector_t size2)
{
	sector_t end = from + size;
	sector_t end2 = from2 + size2;

	if (from >= from2 && from < end2)
		return true;

	if (end > from2 && end <= end2)
		return true;

	if (from2 >= from && from2 < end)
		return true;

	if (end2 > from && end2 <= end)
		return true;

	return false;
}