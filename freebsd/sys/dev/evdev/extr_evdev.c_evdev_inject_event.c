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
typedef  int uint16_t ;
struct evdev_dev {int /*<<< orphan*/  ev_lock_type; TYPE_1__* ev_methods; int /*<<< orphan*/  ev_flags; } ;
typedef  int /*<<< orphan*/  int32_t ;
struct TYPE_2__ {int /*<<< orphan*/  (* ev_event ) (struct evdev_dev*,int,int,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  EVDEV_FLAG_SOFTREPEAT ; 
 int /*<<< orphan*/  EVDEV_LOCK (struct evdev_dev*) ; 
 int /*<<< orphan*/  EVDEV_UNLOCK (struct evdev_dev*) ; 
#define  EV_ABS 137 
#define  EV_FF 136 
#define  EV_KEY 135 
#define  EV_LED 134 
 int /*<<< orphan*/  EV_LOCK_INTERNAL ; 
#define  EV_MSC 133 
#define  EV_REL 132 
#define  EV_REP 131 
#define  EV_SND 130 
#define  EV_SW 129 
#define  EV_SYN 128 
 int /*<<< orphan*/  bit_test (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int evdev_push_event (struct evdev_dev*,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct evdev_dev*,int,int,int /*<<< orphan*/ ) ; 

int
evdev_inject_event(struct evdev_dev *evdev, uint16_t type, uint16_t code,
    int32_t value)
{
	int ret = 0;

	switch (type) {
	case EV_REP:
		/* evdev repeats should not be processed by hardware driver */
		if (bit_test(evdev->ev_flags, EVDEV_FLAG_SOFTREPEAT))
			goto push;
		/* FALLTHROUGH */
	case EV_LED:
	case EV_MSC:
	case EV_SND:
	case EV_FF:
		if (evdev->ev_methods != NULL &&
		    evdev->ev_methods->ev_event != NULL)
			evdev->ev_methods->ev_event(evdev, type, code, value);
		/*
		 * Leds and driver repeats should be reported in ev_event
		 * method body to interoperate with kbdmux states and rates
		 * propagation so both ways (ioctl and evdev) of changing it
		 * will produce only one evdev event report to client.
		 */
		if (type == EV_LED || type == EV_REP)
			break;
		/* FALLTHROUGH */
	case EV_SYN:
	case EV_KEY:
	case EV_REL:
	case EV_ABS:
	case EV_SW:
push:
		if (evdev->ev_lock_type != EV_LOCK_INTERNAL)
			EVDEV_LOCK(evdev);
		ret = evdev_push_event(evdev, type,  code, value);
		if (evdev->ev_lock_type != EV_LOCK_INTERNAL)
			EVDEV_UNLOCK(evdev);
		break;

	default:
		ret = EINVAL;
	}

	return (ret);
}