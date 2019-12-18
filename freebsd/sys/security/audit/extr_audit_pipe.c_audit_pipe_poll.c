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
struct cdev {int dummy; } ;
struct audit_pipe {int /*<<< orphan*/  ap_selinfo; int /*<<< orphan*/  ap_queue; } ;

/* Variables and functions */
 int /*<<< orphan*/  AUDIT_PIPE_LOCK (struct audit_pipe*) ; 
 int /*<<< orphan*/  AUDIT_PIPE_UNLOCK (struct audit_pipe*) ; 
 int POLLIN ; 
 int POLLRDNORM ; 
 int /*<<< orphan*/ * TAILQ_FIRST (int /*<<< orphan*/ *) ; 
 int devfs_get_cdevpriv (void**) ; 
 int /*<<< orphan*/  selrecord (struct thread*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
audit_pipe_poll(struct cdev *dev, int events, struct thread *td)
{
	struct audit_pipe *ap;
	int error, revents;

	revents = 0;
	error = devfs_get_cdevpriv((void **)&ap);
	if (error != 0)
		return (error);
	if (events & (POLLIN | POLLRDNORM)) {
		AUDIT_PIPE_LOCK(ap);
		if (TAILQ_FIRST(&ap->ap_queue) != NULL)
			revents |= events & (POLLIN | POLLRDNORM);
		else
			selrecord(td, &ap->ap_selinfo);
		AUDIT_PIPE_UNLOCK(ap);
	}
	return (revents);
}