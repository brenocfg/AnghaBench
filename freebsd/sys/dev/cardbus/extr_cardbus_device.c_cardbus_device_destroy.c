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
struct cardbus_devinfo {scalar_t__ sc_cisdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  destroy_dev (scalar_t__) ; 

int
cardbus_device_destroy(struct cardbus_devinfo *devi)
{
	if (devi->sc_cisdev)
		destroy_dev(devi->sc_cisdev);
	return (0);
}