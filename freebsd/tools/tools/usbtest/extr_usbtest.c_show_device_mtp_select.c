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
typedef  int /*<<< orphan*/  uint8_t ;

/* Variables and functions */
 int /*<<< orphan*/  USB_TEMP_MTP ; 
 int /*<<< orphan*/  set_template (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
show_device_mtp_select(uint8_t level)
{
	set_template(USB_TEMP_MTP);
}