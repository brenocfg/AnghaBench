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
struct TYPE_2__ {int boot_delay; int /*<<< orphan*/  boot_callout; int /*<<< orphan*/  xpt_taskq; } ;

/* Variables and functions */
 int CAM_DEBUG_BUS ; 
 int CAM_DEBUG_LUN ; 
 scalar_t__ CAM_DEBUG_NONE ; 
 int CAM_DEBUG_TARGET ; 
 scalar_t__ CAM_REQ_CMP ; 
 int /*<<< orphan*/  PRIBIO ; 
 int SBT_1MS ; 
 int /*<<< orphan*/  callout_init (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  callout_reset_sbt (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ cam_dflags ; 
 int /*<<< orphan*/ * cam_dpath ; 
 int /*<<< orphan*/  cam_proc ; 
 scalar_t__ kproc_kthread_add (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  periphdriver_init (int) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 scalar_t__ taskqueue_start_threads (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  xpt_boot_delay ; 
 scalar_t__ xpt_create_path (int /*<<< orphan*/ **,int /*<<< orphan*/ *,int,int,int) ; 
 int /*<<< orphan*/  xpt_hold_boot () ; 
 int /*<<< orphan*/  xpt_scanner_thread ; 
 TYPE_1__ xsoftc ; 

__attribute__((used)) static void
xpt_config(void *arg)
{
	/*
	 * Now that interrupts are enabled, go find our devices
	 */
	if (taskqueue_start_threads(&xsoftc.xpt_taskq, 1, PRIBIO, "CAM taskq"))
		printf("xpt_config: failed to create taskqueue thread.\n");

	/* Setup debugging path */
	if (cam_dflags != CAM_DEBUG_NONE) {
		if (xpt_create_path(&cam_dpath, NULL,
				    CAM_DEBUG_BUS, CAM_DEBUG_TARGET,
				    CAM_DEBUG_LUN) != CAM_REQ_CMP) {
			printf("xpt_config: xpt_create_path() failed for debug"
			       " target %d:%d:%d, debugging disabled\n",
			       CAM_DEBUG_BUS, CAM_DEBUG_TARGET, CAM_DEBUG_LUN);
			cam_dflags = CAM_DEBUG_NONE;
		}
	} else
		cam_dpath = NULL;

	periphdriver_init(1);
	xpt_hold_boot();
	callout_init(&xsoftc.boot_callout, 1);
	callout_reset_sbt(&xsoftc.boot_callout, SBT_1MS * xsoftc.boot_delay, 0,
	    xpt_boot_delay, NULL, 0);
	/* Fire up rescan thread. */
	if (kproc_kthread_add(xpt_scanner_thread, NULL, &cam_proc, NULL, 0, 0,
	    "cam", "scanner")) {
		printf("xpt_config: failed to create rescan thread.\n");
	}
}