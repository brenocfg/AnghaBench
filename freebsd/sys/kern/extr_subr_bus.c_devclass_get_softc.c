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
typedef  int /*<<< orphan*/  device_t ;
typedef  int /*<<< orphan*/  devclass_t ;

/* Variables and functions */
 int /*<<< orphan*/  devclass_get_device (int /*<<< orphan*/ ,int) ; 
 void* device_get_softc (int /*<<< orphan*/ ) ; 

void *
devclass_get_softc(devclass_t dc, int unit)
{
	device_t dev;

	dev = devclass_get_device(dc, unit);
	if (!dev)
		return (NULL);

	return (device_get_softc(dev));
}