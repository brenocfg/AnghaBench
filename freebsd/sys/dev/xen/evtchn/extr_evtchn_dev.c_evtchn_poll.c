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
struct per_user_data {scalar_t__ ring_cons; scalar_t__ ring_prod; int /*<<< orphan*/  ring_prod_mutex; int /*<<< orphan*/  ev_rsel; } ;
struct cdev {int dummy; } ;

/* Variables and functions */
 int POLLERR ; 
 int POLLIN ; 
 int POLLOUT ; 
 int POLLRDNORM ; 
 int POLLWRNORM ; 
 int devfs_get_cdevpriv (void**) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  selrecord (struct thread*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
evtchn_poll(struct cdev *dev, int events, struct thread *td)
{
	struct per_user_data *u;
	int error, mask;

	error = devfs_get_cdevpriv((void **)&u);
	if (error != 0)
		return (POLLERR);

	/* we can always write */
	mask = events & (POLLOUT | POLLWRNORM);

	mtx_lock(&u->ring_prod_mutex);
	if (events & (POLLIN | POLLRDNORM)) {
		if (u->ring_cons != u->ring_prod) {
			mask |= events & (POLLIN | POLLRDNORM);
		} else {
			/* Record that someone is waiting */
			selrecord(td, &u->ev_rsel);
		}
	}
	mtx_unlock(&u->ring_prod_mutex);

	return (mask);
}