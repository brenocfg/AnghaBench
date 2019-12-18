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
struct isp_fc {int /*<<< orphan*/  sim; } ;
struct cam_path {int dummy; } ;
typedef  int /*<<< orphan*/  ispsoftc_t ;
typedef  int /*<<< orphan*/  fcportdb_t ;

/* Variables and functions */
 int /*<<< orphan*/  AC_LOST_DEVICE ; 
 int /*<<< orphan*/  CAM_LUN_WILDCARD ; 
 scalar_t__ CAM_REQ_CMP ; 
 struct isp_fc* ISP_FC_PC (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  cam_sim_path (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xpt_async (int /*<<< orphan*/ ,struct cam_path*,int /*<<< orphan*/ *) ; 
 scalar_t__ xpt_create_path (struct cam_path**,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xpt_free_path (struct cam_path*) ; 

__attribute__((used)) static void
isp_make_gone(ispsoftc_t *isp, fcportdb_t *fcp, int chan, int tgt)
{
	struct cam_path *tp;
	struct isp_fc *fc = ISP_FC_PC(isp, chan);

	if (xpt_create_path(&tp, NULL, cam_sim_path(fc->sim), tgt, CAM_LUN_WILDCARD) == CAM_REQ_CMP) {
		xpt_async(AC_LOST_DEVICE, tp, NULL);
		xpt_free_path(tp);
	}
}