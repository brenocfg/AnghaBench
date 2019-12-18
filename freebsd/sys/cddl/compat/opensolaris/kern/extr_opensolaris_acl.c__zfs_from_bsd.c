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
typedef  int /*<<< orphan*/  uint32_t ;
struct zfs2bsd {int zb_bsd; int /*<<< orphan*/  zb_zfs; } ;

/* Variables and functions */

__attribute__((used)) static uint32_t
_zfs_from_bsd(int bsd, const struct zfs2bsd *table)
{
	const struct zfs2bsd *tmp;
	uint32_t zfs = 0;

	for (tmp = table; tmp->zb_bsd != 0; tmp++) {
		if (bsd & tmp->zb_bsd)
			zfs |= tmp->zb_zfs;
	}

	return (zfs);
}