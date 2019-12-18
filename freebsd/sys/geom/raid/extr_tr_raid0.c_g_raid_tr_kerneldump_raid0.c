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
typedef  int /*<<< orphan*/  vm_offset_t ;
typedef  size_t u_int ;
struct g_raid_volume {scalar_t__ v_state; size_t v_strip_size; size_t v_disks_count; int /*<<< orphan*/ * v_subdisks; } ;
struct g_raid_tr_object {struct g_raid_volume* tro_volume; } ;
typedef  size_t off_t ;

/* Variables and functions */
 int ENXIO ; 
 scalar_t__ G_RAID_VOLUME_S_OPTIMAL ; 
 size_t MIN (size_t,size_t) ; 
 int g_raid_subdisk_kerneldump (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,size_t,size_t) ; 

__attribute__((used)) static int
g_raid_tr_kerneldump_raid0(struct g_raid_tr_object *tr,
    void *virtual, vm_offset_t physical, off_t boffset, size_t blength)
{
	struct g_raid_volume *vol;
	char *addr;
	off_t offset, start, length, nstripe, remain;
	u_int no, strip_size;
	int error;

	vol = tr->tro_volume;
	if (vol->v_state != G_RAID_VOLUME_S_OPTIMAL)
		return (ENXIO);
	addr = virtual;
	strip_size = vol->v_strip_size;

	/* Stripe number. */
	nstripe = boffset / strip_size;
	/* Start position in stripe. */
	start = boffset % strip_size;
	/* Disk number. */
	no = nstripe % vol->v_disks_count;
	/* Stripe tart position in disk. */
	offset = (nstripe / vol->v_disks_count) * strip_size;
	/* Length of data to operate. */
	remain = blength;

	do {
		length = MIN(strip_size - start, remain);
		error = g_raid_subdisk_kerneldump(&vol->v_subdisks[no],
		    addr, 0, offset + start, length);
		if (error != 0)
			return (error);
		if (++no >= vol->v_disks_count) {
			no = 0;
			offset += strip_size;
		}
		remain -= length;
		addr += length;
		start = 0;
	} while (remain > 0);
	return (0);
}