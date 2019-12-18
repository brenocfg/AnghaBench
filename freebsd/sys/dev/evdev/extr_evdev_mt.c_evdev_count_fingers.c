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
struct evdev_dev {int dummy; } ;
typedef  scalar_t__ int32_t ;

/* Variables and functions */
 int /*<<< orphan*/  ABS_MT_TRACKING_ID ; 
 scalar_t__ MAXIMAL_MT_SLOT (struct evdev_dev*) ; 
 int evdev_get_mt_value (struct evdev_dev*,scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int32_t
evdev_count_fingers(struct evdev_dev *evdev)
{
	int32_t nfingers = 0, i;

	for (i = 0; i <= MAXIMAL_MT_SLOT(evdev); i++)
		if (evdev_get_mt_value(evdev, i, ABS_MT_TRACKING_ID) != -1)
			nfingers++;

	return (nfingers);
}