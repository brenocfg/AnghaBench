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
typedef  scalar_t__ u_int ;

/* Variables and functions */

u_int
siba_addrspace_device_region(u_int addrspace)
{
	/* The first addrspace is always mapped to device0.0; the remainder
	 * are mapped to device1.0 + (n - 1) */
	if (addrspace == 0)
		return (0);
	else
		return (addrspace - 1);
}