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
typedef  int /*<<< orphan*/  DSL_DEV_Device_t ;

/* Variables and functions */
 int IFX_MEI_Ioctls (int /*<<< orphan*/ *,int,unsigned int,unsigned long) ; 

int
DSL_BSP_KernelIoctls (DSL_DEV_Device_t * pDev, unsigned int command,
			   unsigned long lon)
{
	int error = 0;

	error = IFX_MEI_Ioctls (pDev, 1, command, lon);
	return error;
}