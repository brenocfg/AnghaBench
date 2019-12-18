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
struct thread {int dummy; } ;
struct ipmi_softc {int dummy; } ;
struct ipmi_device {scalar_t__ ipmi_requests; int /*<<< orphan*/  ipmi_select; int /*<<< orphan*/  ipmi_completed_requests; } ;
struct cdev {struct ipmi_softc* si_drv1; } ;

/* Variables and functions */
 int /*<<< orphan*/  IPMI_LOCK (struct ipmi_softc*) ; 
 int /*<<< orphan*/  IPMI_UNLOCK (struct ipmi_softc*) ; 
 int POLLERR ; 
 int POLLIN ; 
 int POLLRDNORM ; 
 int /*<<< orphan*/  TAILQ_EMPTY (int /*<<< orphan*/ *) ; 
 scalar_t__ devfs_get_cdevpriv (void**) ; 
 int /*<<< orphan*/  selrecord (struct thread*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
ipmi_poll(struct cdev *cdev, int poll_events, struct thread *td)
{
	struct ipmi_device *dev;
	struct ipmi_softc *sc;
	int revents = 0;

	if (devfs_get_cdevpriv((void **)&dev))
		return (0);

	sc = cdev->si_drv1;
	IPMI_LOCK(sc);
	if (poll_events & (POLLIN | POLLRDNORM)) {
		if (!TAILQ_EMPTY(&dev->ipmi_completed_requests))
		    revents |= poll_events & (POLLIN | POLLRDNORM);
		if (dev->ipmi_requests == 0)
		    revents |= POLLERR;
	}

	if (revents == 0) {
		if (poll_events & (POLLIN | POLLRDNORM))
			selrecord(td, &dev->ipmi_select);
	}
	IPMI_UNLOCK(sc);

	return (revents);
}