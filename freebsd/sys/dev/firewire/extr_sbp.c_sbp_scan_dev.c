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
struct sbp_dev {TYPE_1__* target; int /*<<< orphan*/  status; } ;
struct TYPE_2__ {int /*<<< orphan*/  scan_callout; } ;

/* Variables and functions */
 int /*<<< orphan*/  SBP_DEV_PROBE ; 
 int SBT_1MS ; 
 int /*<<< orphan*/  callout_reset_sbt (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sbp_cam_scan_target ; 
 int scan_delay ; 

__attribute__((used)) static __inline void
sbp_scan_dev(struct sbp_dev *sdev)
{
	sdev->status = SBP_DEV_PROBE;
	callout_reset_sbt(&sdev->target->scan_callout, SBT_1MS * scan_delay, 0,
	    sbp_cam_scan_target, (void *)sdev->target, 0);
}