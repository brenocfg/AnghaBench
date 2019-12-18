#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {scalar_t__ async_code; scalar_t__ async_arg_size; void* async_arg_ptr; } ;
struct TYPE_7__ {struct cam_path* path; } ;
union ccb {TYPE_3__ casync; TYPE_1__ ccb_h; } ;
typedef  scalar_t__ u_int32_t ;
struct cam_periph {int dummy; } ;
struct cam_path {struct cam_eb* bus; TYPE_2__* device; } ;
struct cam_eb {int /*<<< orphan*/  sim; int /*<<< orphan*/  last_reset; } ;
struct TYPE_11__ {int /*<<< orphan*/  device; struct cam_eb* bus; } ;
struct TYPE_10__ {TYPE_5__* path; } ;
struct TYPE_8__ {scalar_t__ lun_id; } ;

/* Variables and functions */
 scalar_t__ AC_BUS_RESET ; 
 int /*<<< orphan*/  CAM_DEBUG (struct cam_path*,int,char*) ; 
 int CAM_DEBUG_INFO ; 
 int CAM_DEBUG_TRACE ; 
 scalar_t__ CAM_LUN_WILDCARD ; 
 int /*<<< orphan*/  M_CAMXPT ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  free (void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  microtime (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xpt_async_process_dev (int /*<<< orphan*/ ,union ccb*) ; 
 int /*<<< orphan*/  xpt_async_process_tgt ; 
 int /*<<< orphan*/  xpt_async_string (scalar_t__) ; 
 int /*<<< orphan*/  xpt_free_ccb (union ccb*) ; 
 int /*<<< orphan*/  xpt_free_path (struct cam_path*) ; 
 int /*<<< orphan*/  xpt_path_lock (TYPE_5__*) ; 
 int /*<<< orphan*/  xpt_path_unlock (TYPE_5__*) ; 
 TYPE_4__* xpt_periph ; 
 int /*<<< orphan*/  xpt_release_devq (struct cam_path*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xpt_release_simq (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xpttargettraverse (struct cam_eb*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,union ccb*) ; 

__attribute__((used)) static void
xpt_async_process(struct cam_periph *periph, union ccb *ccb)
{
	struct cam_eb *bus;
	struct cam_path *path;
	void *async_arg;
	u_int32_t async_code;

	path = ccb->ccb_h.path;
	async_code = ccb->casync.async_code;
	async_arg = ccb->casync.async_arg_ptr;
	CAM_DEBUG(path, CAM_DEBUG_TRACE | CAM_DEBUG_INFO,
	    ("xpt_async(%s)\n", xpt_async_string(async_code)));
	bus = path->bus;

	if (async_code == AC_BUS_RESET) {
		/* Update our notion of when the last reset occurred */
		microtime(&bus->last_reset);
	}

	xpttargettraverse(bus, NULL, xpt_async_process_tgt, ccb);

	/*
	 * If this wasn't a fully wildcarded async, tell all
	 * clients that want all async events.
	 */
	if (bus != xpt_periph->path->bus) {
		xpt_path_lock(xpt_periph->path);
		xpt_async_process_dev(xpt_periph->path->device, ccb);
		xpt_path_unlock(xpt_periph->path);
	}

	if (path->device != NULL && path->device->lun_id != CAM_LUN_WILDCARD)
		xpt_release_devq(path, 1, TRUE);
	else
		xpt_release_simq(path->bus->sim, TRUE);
	if (ccb->casync.async_arg_size > 0)
		free(async_arg, M_CAMXPT);
	xpt_free_path(path);
	xpt_free_ccb(ccb);
}