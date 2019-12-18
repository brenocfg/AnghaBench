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
 int /*<<< orphan*/  __gpio_modify_io (unsigned int,unsigned int) ; 
 int /*<<< orphan*/  wb977_close () ; 
 int /*<<< orphan*/  wb977_open () ; 

void nw_gpio_modify_io(unsigned int mask, unsigned int in)
{
	/* Open up the SuperIO chip */
	wb977_open();

	__gpio_modify_io(mask, in);

	/* Close up the EFER gate */
	wb977_close();
}