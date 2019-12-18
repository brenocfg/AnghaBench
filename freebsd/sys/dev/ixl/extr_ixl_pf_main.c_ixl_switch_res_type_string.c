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

char *
ixl_switch_res_type_string(u8 type)
{
	// TODO: This should be changed to static const
	char * ixl_switch_res_type_strings[0x14] = {
		"VEB",
		"VSI",
		"Perfect Match MAC address",
		"S-tag",
		"(Reserved)",
		"Multicast hash entry",
		"Unicast hash entry",
		"VLAN",
		"VSI List entry",
		"(Reserved)",
		"VLAN Statistic Pool",
		"Mirror Rule",
		"Queue Set",
		"Inner VLAN Forward filter",
		"(Reserved)",
		"Inner MAC",
		"IP",
		"GRE/VN1 Key",
		"VN2 Key",
		"Tunneling Port"
	};

	if (type < 0x14)
		return ixl_switch_res_type_strings[type];
	else
		return "(Reserved)";
}