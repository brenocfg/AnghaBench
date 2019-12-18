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
struct evdev_dev {int /*<<< orphan*/  ev_clients; TYPE_1__* ev_methods; int /*<<< orphan*/  ev_shortname; } ;
struct evdev_client {int dummy; } ;
struct TYPE_2__ {int (* ev_open ) (struct evdev_dev*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  EVDEV_LOCK_ASSERT (struct evdev_dev*) ; 
 scalar_t__ LIST_EMPTY (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LIST_INSERT_HEAD (int /*<<< orphan*/ *,struct evdev_client*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  debugf (struct evdev_dev*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ec_link ; 
 int stub1 (struct evdev_dev*) ; 

int
evdev_register_client(struct evdev_dev *evdev, struct evdev_client *client)
{
	int ret = 0;

	debugf(evdev, "adding new client for device %s", evdev->ev_shortname);

	EVDEV_LOCK_ASSERT(evdev);

	if (LIST_EMPTY(&evdev->ev_clients) && evdev->ev_methods != NULL &&
	    evdev->ev_methods->ev_open != NULL) {
		debugf(evdev, "calling ev_open() on device %s",
		    evdev->ev_shortname);
		ret = evdev->ev_methods->ev_open(evdev);
	}
	if (ret == 0)
		LIST_INSERT_HEAD(&evdev->ev_clients, client, ec_link);
	return (ret);
}