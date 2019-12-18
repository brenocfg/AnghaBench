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
typedef  int u8 ;

/* Variables and functions */

__attribute__((used)) static bool zynq_fpga_has_sync(const u8 *buf, size_t count)
{
	for (; count >= 4; buf += 4, count -= 4)
		if (buf[0] == 0x66 && buf[1] == 0x55 && buf[2] == 0x99 &&
		    buf[3] == 0xaa)
			return true;
	return false;
}