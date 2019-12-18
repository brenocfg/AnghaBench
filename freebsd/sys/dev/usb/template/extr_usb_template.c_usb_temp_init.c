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
 int /*<<< orphan*/  usb_temp_get_desc ; 
 int /*<<< orphan*/ * usb_temp_get_desc_p ; 
 int /*<<< orphan*/  usb_temp_setup_by_index ; 
 int /*<<< orphan*/ * usb_temp_setup_by_index_p ; 
 int /*<<< orphan*/  usb_temp_unsetup ; 
 int /*<<< orphan*/ * usb_temp_unsetup_p ; 

__attribute__((used)) static void
usb_temp_init(void *arg)
{
	/* register our functions */
	usb_temp_get_desc_p = &usb_temp_get_desc;
	usb_temp_setup_by_index_p = &usb_temp_setup_by_index;
	usb_temp_unsetup_p = &usb_temp_unsetup;
}