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
typedef  int uint8_t ;
typedef  int uint16_t ;

/* Variables and functions */
 scalar_t__ CF_8 ; 
 scalar_t__ base_addr ; 
 scalar_t__ bus_type ; 

__attribute__((used)) static void cf_outb_8(int port, uint8_t val)
{
	/*
	 * Traditional 8-bit PC Card/CF bus access.
	 */
	if (bus_type == CF_8) {
		volatile uint8_t *task_file = (volatile uint8_t *)base_addr;
		task_file[port] = val;
		return;
	}

	/*
	 * True IDE access.  lower 8 bits on a 16-bit bus (see above).
	 */
	volatile uint16_t *task_file = (volatile uint16_t *)base_addr;
	task_file[port] = val & 0xff;
}