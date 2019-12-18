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
typedef  int uint16_t ;

/* Variables and functions */
 int snprintf (char*,size_t,char*,int) ; 

int
bhnd_format_chip_id(char *buffer, size_t size, uint16_t chip_id)
{
	/* All hex formatted IDs are within the range of 0x4000-0x9C3F (40000-1) */
	if (chip_id >= 0x4000 && chip_id <= 0x9C3F)
		return (snprintf(buffer, size, "BCM%hX", chip_id));
	else
		return (snprintf(buffer, size, "BCM%hu", chip_id));
}