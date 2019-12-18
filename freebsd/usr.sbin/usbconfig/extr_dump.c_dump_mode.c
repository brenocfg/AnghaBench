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
typedef  scalar_t__ uint8_t ;

/* Variables and functions */
 scalar_t__ LIBUSB20_MODE_HOST ; 

const char *
dump_mode(uint8_t value)
{
	if (value == LIBUSB20_MODE_HOST)
		return ("HOST");
	return ("DEVICE");
}