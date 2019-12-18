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
typedef  int u_long ;
struct thread {int dummy; } ;
struct ctl_lun_req {int reqtype; int /*<<< orphan*/  error_str; int /*<<< orphan*/  status; } ;
struct ctl_be_block_softc {int dummy; } ;
struct cdev {int dummy; } ;
typedef  scalar_t__ caddr_t ;

/* Variables and functions */
#define  CTL_LUNREQ_CREATE 131 
#define  CTL_LUNREQ_MODIFY 130 
#define  CTL_LUNREQ_RM 129 
 int /*<<< orphan*/  CTL_LUN_ERROR ; 
#define  CTL_LUN_REQ 128 
 int ENOTTY ; 
 struct ctl_be_block_softc backend_block_softc ; 
 int ctl_be_block_create (struct ctl_be_block_softc*,struct ctl_lun_req*) ; 
 int ctl_be_block_modify (struct ctl_be_block_softc*,struct ctl_lun_req*) ; 
 int ctl_be_block_rm (struct ctl_be_block_softc*,struct ctl_lun_req*) ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,int,char*,int) ; 

__attribute__((used)) static int
ctl_be_block_ioctl(struct cdev *dev, u_long cmd, caddr_t addr,
			int flag, struct thread *td)
{
	struct ctl_be_block_softc *softc;
	int error;

	softc = &backend_block_softc;

	error = 0;

	switch (cmd) {
	case CTL_LUN_REQ: {
		struct ctl_lun_req *lun_req;

		lun_req = (struct ctl_lun_req *)addr;

		switch (lun_req->reqtype) {
		case CTL_LUNREQ_CREATE:
			error = ctl_be_block_create(softc, lun_req);
			break;
		case CTL_LUNREQ_RM:
			error = ctl_be_block_rm(softc, lun_req);
			break;
		case CTL_LUNREQ_MODIFY:
			error = ctl_be_block_modify(softc, lun_req);
			break;
		default:
			lun_req->status = CTL_LUN_ERROR;
			snprintf(lun_req->error_str, sizeof(lun_req->error_str),
				 "invalid LUN request type %d",
				 lun_req->reqtype);
			break;
		}
		break;
	}
	default:
		error = ENOTTY;
		break;
	}

	return (error);
}