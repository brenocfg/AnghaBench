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
struct evdev_dev {int /*<<< orphan*/  ev_prop_flags; } ;

/* Variables and functions */
 scalar_t__ INPUT_PROP_CNT ; 
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int /*<<< orphan*/  bit_set (int /*<<< orphan*/ ,scalar_t__) ; 

inline void
evdev_support_prop(struct evdev_dev *evdev, uint16_t prop)
{

	KASSERT(prop < INPUT_PROP_CNT, ("invalid evdev input property"));
	bit_set(evdev->ev_prop_flags, prop);
}