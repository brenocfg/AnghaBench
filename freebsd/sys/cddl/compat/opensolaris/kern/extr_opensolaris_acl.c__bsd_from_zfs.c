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
typedef  int uint32_t ;
struct zfs2bsd {int zb_zfs; int zb_bsd; } ;

/* Variables and functions */

__attribute__((used)) static int
_bsd_from_zfs(uint32_t zfs, const struct zfs2bsd *table)
{
	const struct zfs2bsd *tmp;
	int bsd = 0;

	for (tmp = table; tmp->zb_zfs != 0; tmp++) {
		if (zfs & tmp->zb_zfs)
			bsd |= tmp->zb_bsd;
	}

	return (bsd);
}