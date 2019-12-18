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
typedef  int u_int ;
struct g_raid_volume {int v_strip_size; int v_disks_count; } ;
typedef  int off_t ;

/* Variables and functions */
 int N ; 

__attribute__((used)) static inline void
P2V(struct g_raid_volume *vol, int disk, off_t offset,
    off_t *virt, int *copy)
{
	off_t nstrip, start;
	u_int strip_size;

	strip_size = vol->v_strip_size;
	/* Start position in strip. */
	start = offset % strip_size;
	/* Physical strip number. */
	nstrip = (offset / strip_size) * vol->v_disks_count + disk;
	/* Number of physical strip (copy) inside virtual strip. */
	*copy = nstrip % N;
	/* Offset in virtual space. */
	*virt = (nstrip / N) * strip_size + start;
}