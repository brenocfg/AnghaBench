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
typedef  int uint32_t ;

/* Variables and functions */
 int /*<<< orphan*/  callout_process (int) ; 
 int hz ; 
 int /*<<< orphan*/  usb_idle () ; 
 int /*<<< orphan*/  usb_init () ; 
 int /*<<< orphan*/  usb_uninit () ; 
 int /*<<< orphan*/  usleep (int) ; 

int
main(int argc, char **argv)
{
	uint32_t time;

	usb_init();

	time = 0;

	while (1) {

		usb_idle();

		usleep(1000);

		if (++time >= (1000 / hz)) {
			time = 0;
			callout_process(1);
		}
	}

	usb_uninit();

	return (0);
}