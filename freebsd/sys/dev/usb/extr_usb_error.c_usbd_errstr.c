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
typedef  size_t usb_error_t ;

/* Variables and functions */
 size_t USB_ERR_MAX ; 
 char const** usb_errstr_table ; 

const char *
usbd_errstr(usb_error_t err)
{
	return (err < USB_ERR_MAX ? usb_errstr_table[err] : "USB_ERR_UNKNOWN");
}