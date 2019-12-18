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

/* Variables and functions */
 int CAM_DATA_RUN_ERR ; 
 int CAM_REQ_CMP_ERR ; 
 int CAM_UNCOR_PARITY ; 
 int XE_BAD_PHASE ; 
 int XE_EXTRA_DATA ; 
 int XE_PARITY_ERR ; 
 int XE_SODL_UNRUN ; 
 int XE_SWIDE_OVRUN ; 

__attribute__((used)) static int sym_xerr_cam_status(int cam_status, int x_status)
{
	if (x_status) {
		if	(x_status & XE_PARITY_ERR)
			cam_status = CAM_UNCOR_PARITY;
		else if	(x_status &(XE_EXTRA_DATA|XE_SODL_UNRUN|XE_SWIDE_OVRUN))
			cam_status = CAM_DATA_RUN_ERR;
		else if	(x_status & XE_BAD_PHASE)
			cam_status = CAM_REQ_CMP_ERR;
		else
			cam_status = CAM_REQ_CMP_ERR;
	}
	return cam_status;
}