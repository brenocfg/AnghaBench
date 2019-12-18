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
typedef  int /*<<< orphan*/  driver_t ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  BUS_ADD_CHILD (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  resource_int_value (char*,int,char*,int*) ; 

__attribute__((used)) static void
nvram2env_identify(driver_t * drv, device_t parent)
{
	int i, ivar;

	for (i = 0; !resource_int_value("nvram", i, "base", &ivar); i++)
		BUS_ADD_CHILD(parent, 0, "nvram2env", i);
}