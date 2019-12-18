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
struct evdev_dev {int /*<<< orphan*/  ev_flags; TYPE_1__* ev_methods; int /*<<< orphan*/  ev_clients; int /*<<< orphan*/  ev_shortname; } ;
struct evdev_client {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* ev_close ) (struct evdev_dev*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  EVDEV_FLAG_SOFTREPEAT ; 
 int /*<<< orphan*/  EVDEV_LOCK_ASSERT (struct evdev_dev*) ; 
 int /*<<< orphan*/  EV_REP ; 
 scalar_t__ LIST_EMPTY (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LIST_REMOVE (struct evdev_client*,int /*<<< orphan*/ ) ; 
 scalar_t__ bit_test (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  debugf (struct evdev_dev*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ec_link ; 
 scalar_t__ evdev_event_supported (struct evdev_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  evdev_release_client (struct evdev_dev*,struct evdev_client*) ; 
 int /*<<< orphan*/  evdev_stop_repeat (struct evdev_dev*) ; 
 int /*<<< orphan*/  stub1 (struct evdev_dev*) ; 

void
evdev_dispose_client(struct evdev_dev *evdev, struct evdev_client *client)
{
	debugf(evdev, "removing client for device %s", evdev->ev_shortname);

	EVDEV_LOCK_ASSERT(evdev);

	LIST_REMOVE(client, ec_link);
	if (LIST_EMPTY(&evdev->ev_clients)) {
		if (evdev->ev_methods != NULL &&
		    evdev->ev_methods->ev_close != NULL)
			(void)evdev->ev_methods->ev_close(evdev);
		if (evdev_event_supported(evdev, EV_REP) &&
		    bit_test(evdev->ev_flags, EVDEV_FLAG_SOFTREPEAT))
			evdev_stop_repeat(evdev);
	}
	evdev_release_client(evdev, client);
}