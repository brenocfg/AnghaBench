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
struct evdev_dev {TYPE_1__* ev_mt; } ;
typedef  int /*<<< orphan*/  int32_t ;
struct TYPE_2__ {int /*<<< orphan*/  ev_mt_last_reported_slot; } ;

/* Variables and functions */

int32_t
evdev_get_last_mt_slot(struct evdev_dev *evdev)
{

	return (evdev->ev_mt->ev_mt_last_reported_slot);
}