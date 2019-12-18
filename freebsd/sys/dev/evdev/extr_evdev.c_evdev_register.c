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
struct evdev_dev {int /*<<< orphan*/  ev_mtx; int /*<<< orphan*/ * ev_lock; int /*<<< orphan*/  ev_lock_type; } ;

/* Variables and functions */
 int /*<<< orphan*/  EV_LOCK_INTERNAL ; 
 int /*<<< orphan*/  MTX_DEF ; 
 int evdev_register_common (struct evdev_dev*) ; 
 int /*<<< orphan*/  mtx_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_init (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int
evdev_register(struct evdev_dev *evdev)
{
	int ret;

	evdev->ev_lock_type = EV_LOCK_INTERNAL;
	evdev->ev_lock = &evdev->ev_mtx;
	mtx_init(&evdev->ev_mtx, "evmtx", NULL, MTX_DEF);

	ret = evdev_register_common(evdev);
	if (ret != 0)
		mtx_destroy(&evdev->ev_mtx);

	return (ret);
}