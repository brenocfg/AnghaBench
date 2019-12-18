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
 int /*<<< orphan*/  ikbd_write (char const*,int) ; 

void ikbd_reset(void)
{
	static const char cmd[2] = { 0x80, 0x01 };

	ikbd_write(cmd, 2);

	/*
	 * if all's well code 0xF1 is returned, else the break codes of
	 * all keys making contact
	 */
}