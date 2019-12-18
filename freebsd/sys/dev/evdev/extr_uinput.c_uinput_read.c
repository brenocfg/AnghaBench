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
struct uio {int uio_resid; TYPE_1__* uio_td; } ;
struct uinput_cdev_state {scalar_t__ ucs_state; int ucs_blocked; size_t ucs_buffer_head; struct input_event* ucs_buffer; int /*<<< orphan*/  ucs_lock; } ;
struct input_event {int dummy; } ;
struct cdev {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  td_tid; } ;

/* Variables and functions */
 int EINVAL ; 
 int EWOULDBLOCK ; 
 int O_NONBLOCK ; 
 int /*<<< orphan*/  PCATCH ; 
 int UINPUT_BUFFER_SIZE ; 
 scalar_t__ UINPUT_EMPTYQ (struct uinput_cdev_state*) ; 
 int /*<<< orphan*/  UINPUT_LOCK (struct uinput_cdev_state*) ; 
 scalar_t__ UINPUT_RUNNING ; 
 int /*<<< orphan*/  UINPUT_UNLOCK (struct uinput_cdev_state*) ; 
 int /*<<< orphan*/  debugf (struct uinput_cdev_state*,char*,int,int /*<<< orphan*/ ) ; 
 int devfs_get_cdevpriv (void**) ; 
 int sx_sleep (struct uinput_cdev_state*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int uiomove (struct input_event*,int,struct uio*) ; 

__attribute__((used)) static int
uinput_read(struct cdev *dev, struct uio *uio, int ioflag)
{
	struct uinput_cdev_state *state;
	struct input_event *event;
	int remaining, ret;

	ret = devfs_get_cdevpriv((void **)&state);
	if (ret != 0)
		return (ret);

	debugf(state, "read %zd bytes by thread %d", uio->uio_resid,
	    uio->uio_td->td_tid);

	/* Zero-sized reads are allowed for error checking */
	if (uio->uio_resid != 0 && uio->uio_resid < sizeof(struct input_event))
		return (EINVAL);

	remaining = uio->uio_resid / sizeof(struct input_event);

	UINPUT_LOCK(state);

	if (state->ucs_state != UINPUT_RUNNING)
		ret = EINVAL;

	if (ret == 0 && UINPUT_EMPTYQ(state)) {
		if (ioflag & O_NONBLOCK)
			ret = EWOULDBLOCK;
		else {
			if (remaining != 0) {
				state->ucs_blocked = true;
				ret = sx_sleep(state, &state->ucs_lock,
				    PCATCH, "uiread", 0);
			}
		}
	}

	while (ret == 0 && !UINPUT_EMPTYQ(state) && remaining > 0) {
		event = &state->ucs_buffer[state->ucs_buffer_head];
		state->ucs_buffer_head = (state->ucs_buffer_head + 1) %
		    UINPUT_BUFFER_SIZE;
		remaining--;
		ret = uiomove(event, sizeof(struct input_event), uio);
	}

	UINPUT_UNLOCK(state);

	return (ret);
}