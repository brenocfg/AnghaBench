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
typedef  int /*<<< orphan*/  device_t ;
struct TYPE_2__ {int /*<<< orphan*/  request_mutex; } ;

/* Variables and functions */
 int bus_generic_suspend (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sx_xlock (int /*<<< orphan*/ *) ; 
 TYPE_1__ xs ; 

__attribute__((used)) static int
xs_suspend(device_t dev)
{
	int error;

	/* Suspend child Xen devices. */
	error = bus_generic_suspend(dev);
	if (error != 0)
		return (error);

	sx_xlock(&xs.request_mutex);

	return (0);
}