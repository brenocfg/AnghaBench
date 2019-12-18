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
typedef  int u_long ;
struct thread {int dummy; } ;
struct cdev {int dummy; } ;
struct autofs_daemon_request {int dummy; } ;
struct autofs_daemon_done_101 {int dummy; } ;
struct autofs_daemon_done {int dummy; } ;
typedef  scalar_t__ caddr_t ;
struct TYPE_2__ {int /*<<< orphan*/  sc_dev_opened; } ;

/* Variables and functions */
#define  AUTOFSDONE 130 
#define  AUTOFSDONE101 129 
#define  AUTOFSREQUEST 128 
 int /*<<< orphan*/  AUTOFS_DEBUG (char*,int) ; 
 int EINVAL ; 
 int /*<<< orphan*/  KASSERT (int /*<<< orphan*/ ,char*) ; 
 int autofs_ioctl_done (struct autofs_daemon_done*) ; 
 int autofs_ioctl_done_101 (struct autofs_daemon_done_101*) ; 
 int autofs_ioctl_request (struct autofs_daemon_request*) ; 
 TYPE_1__* autofs_softc ; 

__attribute__((used)) static int
autofs_ioctl(struct cdev *dev, u_long cmd, caddr_t arg, int mode,
    struct thread *td)
{

	KASSERT(autofs_softc->sc_dev_opened, ("not opened?"));

	switch (cmd) {
	case AUTOFSREQUEST:
		return (autofs_ioctl_request(
		    (struct autofs_daemon_request *)arg));
	case AUTOFSDONE101:
		return (autofs_ioctl_done_101(
		    (struct autofs_daemon_done_101 *)arg));
	case AUTOFSDONE:
		return (autofs_ioctl_done(
		    (struct autofs_daemon_done *)arg));
	default:
		AUTOFS_DEBUG("invalid cmd %lx", cmd);
		return (EINVAL);
	}
}