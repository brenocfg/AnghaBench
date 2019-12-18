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
struct TYPE_2__ {void* status; } ;
struct ccb_calc_geometry {long block_size; int volume_size; int heads; int secs_per_track; int cylinders; TYPE_1__ ccb_h; } ;

/* Variables and functions */
 void* CAM_REQ_CMP ; 
 void* CAM_REQ_CMP_ERR ; 

void
cam_calc_geometry(struct ccb_calc_geometry *ccg, int extended)
{
	uint32_t size_mb, secs_per_cylinder;

	if (ccg->block_size == 0) {
		ccg->ccb_h.status = CAM_REQ_CMP_ERR;
		return;
	}
	size_mb = (1024L * 1024L) / ccg->block_size;
	if (size_mb == 0) {
		ccg->ccb_h.status = CAM_REQ_CMP_ERR;
		return;
	}
	size_mb = ccg->volume_size / size_mb;
	if (size_mb > 1024 && extended) {
		ccg->heads = 255;
		ccg->secs_per_track = 63;
	} else {
		ccg->heads = 64;
		ccg->secs_per_track = 32;
	}
	secs_per_cylinder = ccg->heads * ccg->secs_per_track;
	if (secs_per_cylinder == 0) {
		ccg->ccb_h.status = CAM_REQ_CMP_ERR;
		return;
	}
	ccg->cylinders = ccg->volume_size / secs_per_cylinder;
	ccg->ccb_h.status = CAM_REQ_CMP;
}