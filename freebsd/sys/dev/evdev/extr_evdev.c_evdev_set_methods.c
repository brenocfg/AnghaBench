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
struct evdev_methods {int dummy; } ;
struct evdev_dev {void* ev_softc; struct evdev_methods const* ev_methods; } ;

/* Variables and functions */

inline void
evdev_set_methods(struct evdev_dev *evdev, void *softc,
    const struct evdev_methods *methods)
{

	evdev->ev_methods = methods;
	evdev->ev_softc = softc;
}