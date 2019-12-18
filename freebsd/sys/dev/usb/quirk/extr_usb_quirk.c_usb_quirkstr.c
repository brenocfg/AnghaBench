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
typedef  size_t uint16_t ;

/* Variables and functions */
 size_t USB_QUIRK_MAX ; 
 char const** usb_quirk_str ; 

__attribute__((used)) static const char *
usb_quirkstr(uint16_t quirk)
{
	return ((quirk < USB_QUIRK_MAX && usb_quirk_str[quirk] != NULL) ?
	    usb_quirk_str[quirk] : "UQ_UNKNOWN");
}