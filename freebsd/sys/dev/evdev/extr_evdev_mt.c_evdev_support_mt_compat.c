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
struct evdev_dev {TYPE_1__* ev_absinfo; int /*<<< orphan*/  ev_abs_flags; int /*<<< orphan*/  ev_prop_flags; } ;
typedef  size_t int32_t ;
struct TYPE_2__ {int /*<<< orphan*/  resolution; int /*<<< orphan*/  flat; int /*<<< orphan*/  fuzz; int /*<<< orphan*/  maximum; int /*<<< orphan*/  minimum; int /*<<< orphan*/  value; } ;

/* Variables and functions */
 int /*<<< orphan*/  BTN_TOUCH ; 
 int /*<<< orphan*/  EV_KEY ; 
 size_t INPUT_PROP_DIRECT ; 
 scalar_t__ MAXIMAL_MT_SLOT (struct evdev_dev*) ; 
 scalar_t__ bit_test (int /*<<< orphan*/ ,size_t) ; 
 size_t** evdev_mtstmap ; 
 int /*<<< orphan*/  evdev_support_abs (struct evdev_dev*,size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  evdev_support_event (struct evdev_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  evdev_support_key (struct evdev_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  evdev_support_nfingers (struct evdev_dev*,scalar_t__) ; 
 size_t nitems (size_t**) ; 

void
evdev_support_mt_compat(struct evdev_dev *evdev)
{
	int32_t i;

	if (evdev->ev_absinfo == NULL)
		return;

	evdev_support_event(evdev, EV_KEY);
	evdev_support_key(evdev, BTN_TOUCH);

	/* Touchscreens should not advertise tap tool capabilities */
	if (!bit_test(evdev->ev_prop_flags, INPUT_PROP_DIRECT))
		evdev_support_nfingers(evdev, MAXIMAL_MT_SLOT(evdev) + 1);

	/* Echo 0-th MT-slot as ST-slot */
	for (i = 0; i < nitems(evdev_mtstmap); i++)
		if (bit_test(evdev->ev_abs_flags, evdev_mtstmap[i][0]))
			evdev_support_abs(evdev, evdev_mtstmap[i][1],
			    evdev->ev_absinfo[evdev_mtstmap[i][0]].value,
			    evdev->ev_absinfo[evdev_mtstmap[i][0]].minimum,
			    evdev->ev_absinfo[evdev_mtstmap[i][0]].maximum,
			    evdev->ev_absinfo[evdev_mtstmap[i][0]].fuzz,
			    evdev->ev_absinfo[evdev_mtstmap[i][0]].flat,
			    evdev->ev_absinfo[evdev_mtstmap[i][0]].resolution);
}