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
typedef  scalar_t__ device_t ;

/* Variables and functions */
 int /*<<< orphan*/  Giant ; 
 int /*<<< orphan*/  device_enable (scalar_t__) ; 
 int /*<<< orphan*/  device_is_enabled (scalar_t__) ; 
 int /*<<< orphan*/  device_probe_and_attach (scalar_t__) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
acpi_dock_attach_later(void *context)
{
	device_t	dev;

	dev = (device_t)context;

	if (!device_is_enabled(dev))
		device_enable(dev);

	mtx_lock(&Giant);
	device_probe_and_attach(dev);
	mtx_unlock(&Giant);
}