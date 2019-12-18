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
typedef  size_t uint8_t ;

/* Variables and functions */
 size_t USB_SPEED_MAX ; 
 char const** speed_table ; 

__attribute__((used)) static const char *
usb_speedstr(uint8_t speed)
{
	if (speed >= USB_SPEED_MAX  || speed_table[speed] == NULL)
		return ("UNKNOWN");
	else
		return (speed_table[speed]);
}