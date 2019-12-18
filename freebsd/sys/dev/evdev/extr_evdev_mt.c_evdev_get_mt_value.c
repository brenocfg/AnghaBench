#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct evdev_dev {TYPE_2__* ev_mt; } ;
typedef  size_t int32_t ;
typedef  int /*<<< orphan*/  int16_t ;
struct TYPE_4__ {TYPE_1__* ev_mt_slots; } ;
struct TYPE_3__ {size_t* ev_mt_states; } ;

/* Variables and functions */
 size_t ABS_MT_INDEX (int /*<<< orphan*/ ) ; 

inline int32_t
evdev_get_mt_value(struct evdev_dev *evdev, int32_t slot, int16_t code)
{

	return (evdev->ev_mt->
	    ev_mt_slots[slot].ev_mt_states[ABS_MT_INDEX(code)]);
}