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
 size_t USB_XFERTYPE_MAX ; 
 char const** xfertype_table ; 

__attribute__((used)) static const char *
usb_xferstr(uint8_t type)
{
	if (type >= USB_XFERTYPE_MAX  || xfertype_table[type] == NULL)
		return ("UNKN");
	else
		return (xfertype_table[type]);
}