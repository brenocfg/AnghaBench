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
struct input_event {int /*<<< orphan*/  value; int /*<<< orphan*/  code; int /*<<< orphan*/  type; } ;
struct evdev_dev {int dummy; } ;
struct evdev_client {scalar_t__ ec_revoked; } ;
struct cdev {struct evdev_dev* si_drv1; } ;
struct TYPE_2__ {int /*<<< orphan*/  td_tid; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENODEV ; 
 int /*<<< orphan*/  debugf (struct evdev_client*,char*,...) ; 
 int devfs_get_cdevpriv (void**) ; 
 int evdev_inject_event (struct evdev_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int uiomove (struct input_event*,int,struct uio*) ; 

__attribute__((used)) static int
evdev_write(struct cdev *dev, struct uio *uio, int ioflag)
{
	struct evdev_dev *evdev = dev->si_drv1;
	struct evdev_client *client;
	struct input_event event;
	int ret = 0;

	ret = devfs_get_cdevpriv((void **)&client);
	if (ret != 0)
		return (ret);

	debugf(client, "write %zd bytes by thread %d", uio->uio_resid,
	    uio->uio_td->td_tid);

	if (client->ec_revoked || evdev == NULL)
		return (ENODEV);

	if (uio->uio_resid % sizeof(struct input_event) != 0) {
		debugf(client, "write size not multiple of input_event size");
		return (EINVAL);
	}

	while (uio->uio_resid > 0 && ret == 0) {
		ret = uiomove(&event, sizeof(struct input_event), uio);
		if (ret == 0)
			ret = evdev_inject_event(evdev, event.type, event.code,
			    event.value);
	}

	return (ret);
}