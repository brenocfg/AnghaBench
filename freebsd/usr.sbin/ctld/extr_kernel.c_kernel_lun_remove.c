#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct lun {int /*<<< orphan*/  l_ctl_lun; int /*<<< orphan*/  l_backend; } ;
struct TYPE_3__ {int /*<<< orphan*/  lun_id; } ;
struct TYPE_4__ {TYPE_1__ rm; } ;
struct ctl_lun_req {int status; int error_str; TYPE_2__ reqdata; int /*<<< orphan*/  reqtype; int /*<<< orphan*/  backend; } ;
typedef  int /*<<< orphan*/  req ;

/* Variables and functions */
 int /*<<< orphan*/  CTL_LUNREQ_RM ; 
#define  CTL_LUN_ERROR 130 
#define  CTL_LUN_OK 129 
 int /*<<< orphan*/  CTL_LUN_REQ ; 
#define  CTL_LUN_WARNING 128 
 int /*<<< orphan*/  bzero (struct ctl_lun_req*,int) ; 
 int /*<<< orphan*/  ctl_fd ; 
 int ioctl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct ctl_lun_req*) ; 
 int /*<<< orphan*/  log_warn (char*) ; 
 int /*<<< orphan*/  log_warnx (char*,int) ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

int
kernel_lun_remove(struct lun *lun)
{
	struct ctl_lun_req req;

	bzero(&req, sizeof(req));

	strlcpy(req.backend, lun->l_backend, sizeof(req.backend));
	req.reqtype = CTL_LUNREQ_RM;

	req.reqdata.rm.lun_id = lun->l_ctl_lun;

	if (ioctl(ctl_fd, CTL_LUN_REQ, &req) == -1) {
		log_warn("error issuing CTL_LUN_REQ ioctl");
		return (1);
	}

	switch (req.status) {
	case CTL_LUN_ERROR:
		log_warnx("LUN removal error: %s", req.error_str);
		return (1);
	case CTL_LUN_WARNING:
		log_warnx("LUN removal warning: %s", req.error_str);
		break;
	case CTL_LUN_OK:
		break;
	default:
		log_warnx("unknown LUN removal status: %d", req.status);
		return (1);
	}

	return (0);
}