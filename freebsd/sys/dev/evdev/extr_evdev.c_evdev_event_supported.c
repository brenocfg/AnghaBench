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
struct evdev_dev {int /*<<< orphan*/  ev_type_flags; } ;

/* Variables and functions */
 scalar_t__ EV_CNT ; 
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int bit_test (int /*<<< orphan*/ ,scalar_t__) ; 

bool
evdev_event_supported(struct evdev_dev *evdev, uint16_t type)
{

	KASSERT(type < EV_CNT, ("invalid evdev event property"));
	return (bit_test(evdev->ev_type_flags, type));
}