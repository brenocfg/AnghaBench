#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int async_arg_size; int /*<<< orphan*/ * async_arg_ptr; int /*<<< orphan*/  async_code; } ;
struct TYPE_8__ {TYPE_5__* path; int /*<<< orphan*/  func_code; int /*<<< orphan*/  flags; int /*<<< orphan*/  cbfcnp; } ;
union ccb {TYPE_2__ casync; TYPE_1__ ccb_h; } ;
typedef  int /*<<< orphan*/  u_int32_t ;
struct cam_path {TYPE_4__* bus; TYPE_3__* device; } ;
struct TYPE_12__ {int /*<<< orphan*/ * periph; } ;
struct TYPE_11__ {int /*<<< orphan*/  sim; } ;
struct TYPE_10__ {scalar_t__ lun_id; } ;

/* Variables and functions */
 int /*<<< orphan*/  CAM_DEBUG (TYPE_5__*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  CAM_DEBUG_TRACE ; 
 scalar_t__ CAM_LUN_WILDCARD ; 
 scalar_t__ CAM_REQ_CMP ; 
 int /*<<< orphan*/  CAM_UNLOCKED ; 
 int /*<<< orphan*/  M_CAMXPT ; 
 int /*<<< orphan*/  M_NOWAIT ; 
 int /*<<< orphan*/  XPT_ASYNC ; 
 int /*<<< orphan*/ * malloc (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,void*,int) ; 
 int /*<<< orphan*/  xpt_action_name (int /*<<< orphan*/ ) ; 
 union ccb* xpt_alloc_ccb_nowait () ; 
 int /*<<< orphan*/  xpt_async_process ; 
 int xpt_async_size (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xpt_async_string (int /*<<< orphan*/ ) ; 
 scalar_t__ xpt_clone_path (TYPE_5__**,struct cam_path*) ; 
 int /*<<< orphan*/  xpt_done (union ccb*) ; 
 int /*<<< orphan*/  xpt_free_ccb (union ccb*) ; 
 int /*<<< orphan*/  xpt_free_path (TYPE_5__*) ; 
 int /*<<< orphan*/  xpt_freeze_devq (struct cam_path*,int) ; 
 int /*<<< orphan*/  xpt_freeze_simq (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  xpt_print (struct cam_path*,char*,int /*<<< orphan*/ ) ; 

void
xpt_async(u_int32_t async_code, struct cam_path *path, void *async_arg)
{
	union ccb *ccb;
	int size;

	ccb = xpt_alloc_ccb_nowait();
	if (ccb == NULL) {
		xpt_print(path, "Can't allocate CCB to send %s\n",
		    xpt_async_string(async_code));
		return;
	}

	if (xpt_clone_path(&ccb->ccb_h.path, path) != CAM_REQ_CMP) {
		xpt_print(path, "Can't allocate path to send %s\n",
		    xpt_async_string(async_code));
		xpt_free_ccb(ccb);
		return;
	}
	ccb->ccb_h.path->periph = NULL;
	ccb->ccb_h.func_code = XPT_ASYNC;
	ccb->ccb_h.cbfcnp = xpt_async_process;
	ccb->ccb_h.flags |= CAM_UNLOCKED;
	ccb->casync.async_code = async_code;
	ccb->casync.async_arg_size = 0;
	size = xpt_async_size(async_code);
	CAM_DEBUG(ccb->ccb_h.path, CAM_DEBUG_TRACE,
	    ("xpt_async: func %#x %s aync_code %d %s\n",
		ccb->ccb_h.func_code,
		xpt_action_name(ccb->ccb_h.func_code),
		async_code,
		xpt_async_string(async_code)));
	if (size > 0 && async_arg != NULL) {
		ccb->casync.async_arg_ptr = malloc(size, M_CAMXPT, M_NOWAIT);
		if (ccb->casync.async_arg_ptr == NULL) {
			xpt_print(path, "Can't allocate argument to send %s\n",
			    xpt_async_string(async_code));
			xpt_free_path(ccb->ccb_h.path);
			xpt_free_ccb(ccb);
			return;
		}
		memcpy(ccb->casync.async_arg_ptr, async_arg, size);
		ccb->casync.async_arg_size = size;
	} else if (size < 0) {
		ccb->casync.async_arg_ptr = async_arg;
		ccb->casync.async_arg_size = size;
	}
	if (path->device != NULL && path->device->lun_id != CAM_LUN_WILDCARD)
		xpt_freeze_devq(path, 1);
	else
		xpt_freeze_simq(path->bus->sim, 1);
	xpt_done(ccb);
}