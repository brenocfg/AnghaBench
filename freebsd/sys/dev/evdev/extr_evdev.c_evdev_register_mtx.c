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
struct mtx {int dummy; } ;
struct evdev_dev {struct mtx* ev_lock; int /*<<< orphan*/  ev_lock_type; } ;

/* Variables and functions */
 int /*<<< orphan*/  EV_LOCK_MTX ; 
 int evdev_register_common (struct evdev_dev*) ; 

int
evdev_register_mtx(struct evdev_dev *evdev, struct mtx *mtx)
{

	evdev->ev_lock_type = EV_LOCK_MTX;
	evdev->ev_lock = mtx;
	return (evdev_register_common(evdev));
}