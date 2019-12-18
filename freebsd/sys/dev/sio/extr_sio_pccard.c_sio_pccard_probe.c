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
typedef  scalar_t__ u_int32_t ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int ENXIO ; 
 scalar_t__ PCCARD_FUNCTION_SERIAL ; 
 scalar_t__ PCCARD_FUNCTION_UNSPEC ; 
 int pccard_get_function (int /*<<< orphan*/ ,scalar_t__*) ; 

__attribute__((used)) static int
sio_pccard_probe(device_t dev)
{
	int		error = 0;
	u_int32_t	fcn = PCCARD_FUNCTION_UNSPEC;

	error = pccard_get_function(dev, &fcn);
	if (error != 0)
		return (error);

	/*
	 * If a serial card, we are likely the right driver.  However,
	 * some serial cards are better servered by other drivers, so
	 * allow other drivers to claim it, if they want.
	 */
	if (fcn == PCCARD_FUNCTION_SERIAL)
		return (-100);
	return (ENXIO);
}