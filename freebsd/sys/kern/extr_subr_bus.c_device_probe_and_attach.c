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

/* Variables and functions */
 int /*<<< orphan*/  CURVNET_RESTORE () ; 
 int /*<<< orphan*/  CURVNET_SET_QUIET (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GIANT_REQUIRED ; 
 int device_attach (int /*<<< orphan*/ ) ; 
 int device_probe (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vnet0 ; 

int
device_probe_and_attach(device_t dev)
{
	int error;

	GIANT_REQUIRED;

	error = device_probe(dev);
	if (error == -1)
		return (0);
	else if (error != 0)
		return (error);

	CURVNET_SET_QUIET(vnet0);
	error = device_attach(dev);
	CURVNET_RESTORE();
	return error;
}