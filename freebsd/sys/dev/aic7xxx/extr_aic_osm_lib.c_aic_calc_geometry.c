#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
struct TYPE_2__ {int /*<<< orphan*/  status; } ;
struct ccb_calc_geometry {long volume_size; long block_size; int heads; int secs_per_track; int cylinders; TYPE_1__ ccb_h; } ;

/* Variables and functions */
 int /*<<< orphan*/  CAM_REQ_CMP ; 
 int /*<<< orphan*/  cam_calc_geometry (struct ccb_calc_geometry*,int) ; 

void
aic_calc_geometry(struct ccb_calc_geometry *ccg, int extended)
{
#if __FreeBSD_version >= 500000
	cam_calc_geometry(ccg, extended);
#else
	uint32_t size_mb;
	uint32_t secs_per_cylinder;

	size_mb = ccg->volume_size / ((1024L * 1024L) / ccg->block_size);
	if (size_mb > 1024 && extended) {
		ccg->heads = 255;
		ccg->secs_per_track = 63;
	} else {
		ccg->heads = 64;
		ccg->secs_per_track = 32;
	}
	secs_per_cylinder = ccg->heads * ccg->secs_per_track;
	ccg->cylinders = ccg->volume_size / secs_per_cylinder;
	ccg->ccb_h.status = CAM_REQ_CMP;
#endif
}