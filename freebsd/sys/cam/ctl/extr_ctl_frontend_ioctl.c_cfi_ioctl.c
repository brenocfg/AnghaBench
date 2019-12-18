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
typedef  scalar_t__ u_long ;
struct thread {int dummy; } ;
struct ctl_req {int reqtype; int /*<<< orphan*/  error_str; int /*<<< orphan*/  status; } ;
struct cdev {int dummy; } ;
typedef  scalar_t__ caddr_t ;

/* Variables and functions */
 int /*<<< orphan*/  CTL_LUN_ERROR ; 
 scalar_t__ CTL_PORT_REQ ; 
#define  CTL_REQ_CREATE 129 
#define  CTL_REQ_REMOVE 128 
 int ENOTTY ; 
 int /*<<< orphan*/  cfi_ioctl_port_create (struct ctl_req*) ; 
 int /*<<< orphan*/  cfi_ioctl_port_remove (struct ctl_req*) ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,int,char*,int) ; 

__attribute__((used)) static int
cfi_ioctl(struct cdev *dev, u_long cmd, caddr_t addr, int flag,
    struct thread *td)
{
	struct ctl_req *req;

	if (cmd == CTL_PORT_REQ) {
		req = (struct ctl_req *)addr;
		switch (req->reqtype) {
		case CTL_REQ_CREATE:
			cfi_ioctl_port_create(req);
			break;
		case CTL_REQ_REMOVE:
			cfi_ioctl_port_remove(req);
			break;
		default:
			req->status = CTL_LUN_ERROR;
			snprintf(req->error_str, sizeof(req->error_str),
			    "Unsupported request type %d", req->reqtype);
		}
		return (0);
	}

	return (ENOTTY);
}