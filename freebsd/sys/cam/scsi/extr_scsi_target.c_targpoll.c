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
struct targ_softc {int /*<<< orphan*/  read_select; int /*<<< orphan*/  periph; int /*<<< orphan*/  abort_queue; int /*<<< orphan*/  user_ccb_queue; } ;
struct cdev {int dummy; } ;

/* Variables and functions */
 int POLLIN ; 
 int POLLOUT ; 
 int POLLRDNORM ; 
 int POLLWRNORM ; 
 int /*<<< orphan*/  TAILQ_EMPTY (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cam_periph_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cam_periph_unlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devfs_get_cdevpriv (void**) ; 
 int /*<<< orphan*/  selrecord (struct thread*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
targpoll(struct cdev *dev, int poll_events, struct thread *td)
{
	struct targ_softc *softc;
	int	revents;

	devfs_get_cdevpriv((void **)&softc);

	/* Poll for write() is always ok. */
	revents = poll_events & (POLLOUT | POLLWRNORM);
	if ((poll_events & (POLLIN | POLLRDNORM)) != 0) {
		/* Poll for read() depends on user and abort queues. */
		cam_periph_lock(softc->periph);
		if (!TAILQ_EMPTY(&softc->user_ccb_queue) ||
		    !TAILQ_EMPTY(&softc->abort_queue)) {
			revents |= poll_events & (POLLIN | POLLRDNORM);
		}
		cam_periph_unlock(softc->periph);
		/* Only sleep if the user didn't poll for write. */
		if (revents == 0)
			selrecord(td, &softc->read_select);
	}

	return (revents);
}