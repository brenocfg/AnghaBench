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
typedef  int uint32_t ;
struct TYPE_2__ {int /*<<< orphan*/ * device; } ;

/* Variables and functions */
 int /*<<< orphan*/  callout_process (int) ; 
 int /*<<< orphan*/  delay (int) ; 
 int hz ; 
 TYPE_1__ umass_uaa ; 
 int /*<<< orphan*/  usb_idle () ; 
 int /*<<< orphan*/  usb_init () ; 
 int /*<<< orphan*/  usb_needs_explore_all () ; 

__attribute__((used)) static int
umass_disk_init(void)
{
	uint32_t time;

	usb_init();
	usb_needs_explore_all();

	/* wait 8 seconds for a USB mass storage device to appear */
	for (time = 0; time < (8 * hz); time++) {
		usb_idle();
		delay(1000000 / hz);
		time++;
		callout_process(1);
		if (umass_uaa.device != NULL)
			return (0);
	}
	return (0);
}