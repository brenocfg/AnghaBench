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
typedef  size_t uint32_t ;

/* Variables and functions */
 size_t USB_ERR_MAX ; 
 char const** errstr_table ; 

__attribute__((used)) static const char *
usb_errstr(uint32_t error)
{
	if (error >= USB_ERR_MAX || errstr_table[error] == NULL)
		return ("UNKNOWN");
	else
		return (errstr_table[error]);
}