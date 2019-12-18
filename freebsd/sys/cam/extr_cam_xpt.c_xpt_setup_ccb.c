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
typedef  int /*<<< orphan*/  u_int32_t ;
struct ccb_hdr {int dummy; } ;
struct cam_path {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  xpt_setup_ccb_flags (struct ccb_hdr*,struct cam_path*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
xpt_setup_ccb(struct ccb_hdr *ccb_h, struct cam_path *path, u_int32_t priority)
{
	xpt_setup_ccb_flags(ccb_h, path, priority, /*flags*/ 0);
}