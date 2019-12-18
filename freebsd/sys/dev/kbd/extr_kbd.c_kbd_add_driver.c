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
typedef  int /*<<< orphan*/  keyboard_driver_t ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  SLIST_INSERT_HEAD (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ SLIST_NEXT (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  keyboard_drivers ; 
 int /*<<< orphan*/  link ; 

int
kbd_add_driver(keyboard_driver_t *driver)
{
	if (SLIST_NEXT(driver, link))
		return (EINVAL);
	SLIST_INSERT_HEAD(&keyboard_drivers, driver, link);
	return (0);
}