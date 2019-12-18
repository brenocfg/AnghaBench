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
typedef  union ccb {int dummy; } ccb ;
typedef  int /*<<< orphan*/  u_int16_t ;
struct TYPE_2__ {int status; int /*<<< orphan*/  func_code; } ;
struct ccb_pathinq {int target_sprt; int /*<<< orphan*/  hba_inquiry; TYPE_1__ ccb_h; } ;
typedef  int /*<<< orphan*/  cpi ;
typedef  int cam_status ;

/* Variables and functions */
 int CAM_PATH_INVALID ; 
 int CAM_REQ_CMP ; 
 int CAM_STATUS_MASK ; 
 int PIT_PROCESSOR ; 
 int /*<<< orphan*/  XPT_PATH_INQ ; 
 int /*<<< orphan*/  bzero (struct ccb_pathinq*,int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  send_ccb (union ccb*,int) ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static cam_status
get_sim_flags(u_int16_t *flags)
{
	struct ccb_pathinq cpi;
	cam_status status;

	/* Find SIM capabilities */
	bzero(&cpi, sizeof(cpi));
	cpi.ccb_h.func_code = XPT_PATH_INQ;
	send_ccb((union ccb *)&cpi, /*priority*/1);
	status = cpi.ccb_h.status & CAM_STATUS_MASK;
	if (status != CAM_REQ_CMP) {
		fprintf(stderr, "CPI failed, status %#x\n", status);
		return (status);
	}

	/* Can only enable on controllers that support target mode */
	if ((cpi.target_sprt & PIT_PROCESSOR) == 0) {
		fprintf(stderr, "HBA does not support target mode\n");
		status = CAM_PATH_INVALID;
		return (status);
	}

	*flags = cpi.hba_inquiry;
	return (status);
}