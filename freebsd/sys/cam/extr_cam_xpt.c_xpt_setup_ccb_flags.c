#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  void* u_int32_t ;
struct TYPE_12__ {int /*<<< orphan*/  index; scalar_t__ generation; void* priority; } ;
struct ccb_hdr {scalar_t__ xflags; void* flags; TYPE_6__ pinfo; void* target_lun; void* target_id; int /*<<< orphan*/  path_id; struct cam_path* path; } ;
struct cam_path {TYPE_5__* device; TYPE_2__* target; TYPE_1__* bus; } ;
struct TYPE_9__ {scalar_t__ generation; } ;
struct TYPE_10__ {TYPE_3__ queue; } ;
struct TYPE_11__ {TYPE_4__ ccbq; void* lun_id; } ;
struct TYPE_8__ {void* target_id; } ;
struct TYPE_7__ {int /*<<< orphan*/  path_id; } ;

/* Variables and functions */
 int /*<<< orphan*/  CAM_DEBUG (struct cam_path*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  CAM_DEBUG_TRACE ; 
 void* CAM_TARGET_WILDCARD ; 
 int /*<<< orphan*/  CAM_UNQUEUED_INDEX ; 

void
xpt_setup_ccb_flags(struct ccb_hdr *ccb_h, struct cam_path *path,
		    u_int32_t priority, u_int32_t flags)
{

	CAM_DEBUG(path, CAM_DEBUG_TRACE, ("xpt_setup_ccb\n"));
	ccb_h->pinfo.priority = priority;
	ccb_h->path = path;
	ccb_h->path_id = path->bus->path_id;
	if (path->target)
		ccb_h->target_id = path->target->target_id;
	else
		ccb_h->target_id = CAM_TARGET_WILDCARD;
	if (path->device) {
		ccb_h->target_lun = path->device->lun_id;
		ccb_h->pinfo.generation = ++path->device->ccbq.queue.generation;
	} else {
		ccb_h->target_lun = CAM_TARGET_WILDCARD;
	}
	ccb_h->pinfo.index = CAM_UNQUEUED_INDEX;
	ccb_h->flags = flags;
	ccb_h->xflags = 0;
}