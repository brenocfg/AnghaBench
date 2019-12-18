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
struct uinput_user_dev {int /*<<< orphan*/  value; int /*<<< orphan*/  code; int /*<<< orphan*/  type; } ;
struct uinput_cdev_state {scalar_t__ ucs_state; int /*<<< orphan*/  ucs_evdev; } ;
struct input_event {int /*<<< orphan*/  value; int /*<<< orphan*/  code; int /*<<< orphan*/  type; } ;
struct cdev {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  td_tid; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  UINPUT_LOCK (struct uinput_cdev_state*) ; 
 scalar_t__ UINPUT_RUNNING ; 
 int /*<<< orphan*/  UINPUT_UNLOCK (struct uinput_cdev_state*) ; 
 int /*<<< orphan*/  debugf (struct uinput_cdev_state*,char*,...) ; 
 int devfs_get_cdevpriv (void**) ; 
 int evdev_push_event (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uinput_setup_provider (struct uinput_cdev_state*,struct uinput_user_dev*) ; 
 int uiomove (struct uinput_user_dev*,int,struct uio*) ; 

__attribute__((used)) static int
uinput_write(struct cdev *dev, struct uio *uio, int ioflag)
{
	struct uinput_cdev_state *state;
	struct uinput_user_dev userdev;
	struct input_event event;
	int ret = 0;

	ret = devfs_get_cdevpriv((void **)&state);
	if (ret != 0)
		return (ret);

	debugf(state, "write %zd bytes by thread %d", uio->uio_resid,
	    uio->uio_td->td_tid);

	UINPUT_LOCK(state);

	if (state->ucs_state != UINPUT_RUNNING) {
		/* Process written struct uinput_user_dev */
		if (uio->uio_resid != sizeof(struct uinput_user_dev)) {
			debugf(state, "write size not multiple of "
			    "struct uinput_user_dev size");
			ret = EINVAL;
		} else {
			ret = uiomove(&userdev, sizeof(struct uinput_user_dev),
			    uio);
			if (ret == 0)
				uinput_setup_provider(state, &userdev);
		}
	} else {
		/* Process written event */
		if (uio->uio_resid % sizeof(struct input_event) != 0) {
			debugf(state, "write size not multiple of "
			    "struct input_event size");
			ret = EINVAL;
		}

		while (ret == 0 && uio->uio_resid > 0) {
			uiomove(&event, sizeof(struct input_event), uio);
			ret = evdev_push_event(state->ucs_evdev, event.type,
			    event.code, event.value);
		}
	}

	UINPUT_UNLOCK(state);

	return (ret);
}