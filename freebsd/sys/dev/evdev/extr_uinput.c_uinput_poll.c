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
struct uinput_cdev_state {int ucs_selected; int /*<<< orphan*/  ucs_selp; } ;
struct thread {int /*<<< orphan*/  td_tid; } ;
struct cdev {int dummy; } ;

/* Variables and functions */
 int POLLIN ; 
 int POLLNVAL ; 
 int POLLOUT ; 
 int POLLRDNORM ; 
 int POLLWRNORM ; 
 int /*<<< orphan*/  UINPUT_EMPTYQ (struct uinput_cdev_state*) ; 
 int /*<<< orphan*/  UINPUT_LOCK (struct uinput_cdev_state*) ; 
 int /*<<< orphan*/  UINPUT_UNLOCK (struct uinput_cdev_state*) ; 
 int /*<<< orphan*/  debugf (struct uinput_cdev_state*,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ devfs_get_cdevpriv (void**) ; 
 int /*<<< orphan*/  selrecord (struct thread*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
uinput_poll(struct cdev *dev, int events, struct thread *td)
{
	struct uinput_cdev_state *state;
	int revents = 0;

	if (devfs_get_cdevpriv((void **)&state) != 0)
		return (POLLNVAL);

	debugf(state, "poll by thread %d", td->td_tid);

	/* Always allow write */
	if (events & (POLLOUT | POLLWRNORM))
		revents |= (events & (POLLOUT | POLLWRNORM));

	if (events & (POLLIN | POLLRDNORM)) {
		UINPUT_LOCK(state);
		if (!UINPUT_EMPTYQ(state))
			revents = events & (POLLIN | POLLRDNORM);
		else {
			state->ucs_selected = true;
			selrecord(td, &state->ucs_selp);
		}
		UINPUT_UNLOCK(state);
	}

	return (revents);
}