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
typedef  scalar_t__ uint32_t ;
struct TYPE_2__ {scalar_t__ linux_code; scalar_t__ bsd_code; } ;

/* Variables and functions */
 scalar_t__ GPIOKEY_NONE ; 
 TYPE_1__* gpiokeys_codes_map ; 

uint32_t
gpiokey_map_linux_code(uint32_t linux_code)
{
	int i;

	for (i = 0; gpiokeys_codes_map[i].linux_code != GPIOKEY_NONE; i++) {
		if (gpiokeys_codes_map[i].linux_code == linux_code)
			return (gpiokeys_codes_map[i].bsd_code);
	}

	return (GPIOKEY_NONE);
}