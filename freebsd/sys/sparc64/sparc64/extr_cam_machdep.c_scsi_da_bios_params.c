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
typedef  int uint64_t ;
typedef  int uint32_t ;
struct ccb_calc_geometry {long block_size; int volume_size; int heads; int secs_per_track; int cylinders; } ;

/* Variables and functions */

int
scsi_da_bios_params(struct ccb_calc_geometry *ccg)
{
	uint32_t secs_per_cylinder, size_mb;

	/*
	 * The VTOC8 disk label only uses 16-bit fields for cylinders, heads
	 * and sectors so the geometry of large disks has to be adjusted.
	 * We generally use the sizing used by cam_calc_geometry(9), except
	 * when it would overflow the cylinders, in which case we use 255
	 * heads and sectors.  This allows disks up to the 2TB limit of the
	 * extended VTOC8.
	 * XXX this doesn't match the sizing used by OpenSolaris, as that
	 * would exceed the 8-bit ccg->heads and ccg->secs_per_track.
	 */
	if (ccg->block_size == 0)
		return (0);
	size_mb = (1024L * 1024L) / ccg->block_size;
	if (size_mb == 0)
		return (0);
	size_mb = ccg->volume_size / size_mb;
	if (ccg->volume_size > (uint64_t)65535 * 255 * 63) {
		ccg->heads = 255;
		ccg->secs_per_track = 255;
	} else if (size_mb > 1024) {
		ccg->heads = 255;
		ccg->secs_per_track = 63;
	} else {
		ccg->heads = 64;
		ccg->secs_per_track = 32;
	}
	secs_per_cylinder = ccg->heads * ccg->secs_per_track;
	if (secs_per_cylinder == 0)
		return (0);
	ccg->cylinders = ccg->volume_size / secs_per_cylinder;
	return (1);
}