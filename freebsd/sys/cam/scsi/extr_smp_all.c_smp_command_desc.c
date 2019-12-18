#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint8_t ;
struct TYPE_3__ {scalar_t__ cmd_num; char const* desc; } ;

/* Variables and functions */
 int nitems (TYPE_1__*) ; 
 TYPE_1__* smp_cmd_table ; 

const char *
smp_command_desc(uint8_t cmd_num)
{
	int i;

	for (i = 0; i < nitems(smp_cmd_table) &&
	     smp_cmd_table[i].cmd_num <= cmd_num; i++) {
		if (cmd_num == smp_cmd_table[i].cmd_num)
			return (smp_cmd_table[i].desc);
	}

	/*
	 * 0x40 to 0x7f and 0xc0 to 0xff are the vendor specific SMP
	 * command ranges.
	 */
	if (((cmd_num >= 0x40) && (cmd_num <= 0x7f))
	 || (cmd_num >= 0xc0)) {
		return ("Vendor Specific SMP Command");
	} else {
		return ("Unknown SMP Command");
	}
}