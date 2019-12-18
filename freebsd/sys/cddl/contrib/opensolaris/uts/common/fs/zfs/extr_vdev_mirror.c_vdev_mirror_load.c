#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {scalar_t__ vdev_nonrot; } ;
typedef  TYPE_1__ vdev_t ;
typedef  scalar_t__ uint64_t ;
struct TYPE_8__ {scalar_t__ mm_root; } ;
typedef  TYPE_2__ mirror_map_t ;

/* Variables and functions */
 scalar_t__ ABS (scalar_t__) ; 
 int INT_MAX ; 
 int non_rotating_inc ; 
 int non_rotating_seek_inc ; 
 int rotating_inc ; 
 int rotating_seek_inc ; 
 scalar_t__ rotating_seek_offset ; 
 scalar_t__ vdev_queue_lastoffset (TYPE_1__*) ; 
 int vdev_queue_length (TYPE_1__*) ; 

__attribute__((used)) static int
vdev_mirror_load(mirror_map_t *mm, vdev_t *vd, uint64_t zio_offset)
{
	uint64_t lastoffset;
	int load;

	/* All DVAs have equal weight at the root. */
	if (mm->mm_root)
		return (INT_MAX);

	/*
	 * We don't return INT_MAX if the device is resilvering i.e.
	 * vdev_resilver_txg != 0 as when tested performance was slightly
	 * worse overall when resilvering with compared to without.
	 */

	/* Standard load based on pending queue length. */
	load = vdev_queue_length(vd);
	lastoffset = vdev_queue_lastoffset(vd);

	if (vd->vdev_nonrot) {
		/* Non-rotating media. */
		if (lastoffset == zio_offset)
			return (load + non_rotating_inc);

		/*
		 * Apply a seek penalty even for non-rotating devices as
		 * sequential I/O'a can be aggregated into fewer operations
		 * on the device, thus avoiding unnecessary per-command
		 * overhead and boosting performance.
		 */
		return (load + non_rotating_seek_inc);
	}

	/* Rotating media I/O's which directly follow the last I/O. */
	if (lastoffset == zio_offset)
		return (load + rotating_inc);

	/*
	 * Apply half the seek increment to I/O's within seek offset
	 * of the last I/O queued to this vdev as they should incure less
	 * of a seek increment.
	 */
	if (ABS(lastoffset - zio_offset) < rotating_seek_offset)
		return (load + (rotating_seek_inc / 2));

	/* Apply the full seek increment to all other I/O's. */
	return (load + rotating_seek_inc);
}