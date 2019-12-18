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

/* Variables and functions */
 int /*<<< orphan*/  hz ; 
 int /*<<< orphan*/  pause (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * usb_temp_get_desc_p ; 
 int /*<<< orphan*/  usb_temp_get_desc_w ; 
 int /*<<< orphan*/ * usb_temp_setup_by_index_p ; 
 int /*<<< orphan*/  usb_temp_setup_by_index_w ; 
 int /*<<< orphan*/ * usb_temp_unsetup_p ; 
 int /*<<< orphan*/  usb_temp_unsetup_w ; 

void
usb_temp_unload(void *arg)
{
	/* reset function pointers */

	usb_temp_get_desc_p = &usb_temp_get_desc_w;
	usb_temp_setup_by_index_p = &usb_temp_setup_by_index_w;
	usb_temp_unsetup_p = &usb_temp_unsetup_w;

	/* wait for CPU to exit the loaded functions, if any */

	/* XXX this is a tradeoff */

	pause("WAIT", hz);
}