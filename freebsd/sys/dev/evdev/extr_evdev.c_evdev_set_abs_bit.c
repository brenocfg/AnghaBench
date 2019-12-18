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
typedef  scalar_t__ uint16_t ;
struct evdev_dev {int /*<<< orphan*/  ev_abs_flags; int /*<<< orphan*/ * ev_absinfo; } ;

/* Variables and functions */
 scalar_t__ ABS_CNT ; 
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int /*<<< orphan*/  bit_set (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/ * evdev_alloc_absinfo () ; 

inline void
evdev_set_abs_bit(struct evdev_dev *evdev, uint16_t code)
{

	KASSERT(code < ABS_CNT, ("invalid evdev abs property"));
	if (evdev->ev_absinfo == NULL)
		evdev->ev_absinfo = evdev_alloc_absinfo();
	bit_set(evdev->ev_abs_flags, code);
}