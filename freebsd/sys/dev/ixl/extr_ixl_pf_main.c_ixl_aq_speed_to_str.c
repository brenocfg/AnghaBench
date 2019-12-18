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
typedef  enum i40e_aq_link_speed { ____Placeholder_i40e_aq_link_speed } i40e_aq_link_speed ;

/* Variables and functions */
#define  I40E_LINK_SPEED_100MB 134 
#define  I40E_LINK_SPEED_10GB 133 
#define  I40E_LINK_SPEED_1GB 132 
#define  I40E_LINK_SPEED_20GB 131 
#define  I40E_LINK_SPEED_25GB 130 
#define  I40E_LINK_SPEED_40GB 129 
#define  I40E_LINK_SPEED_UNKNOWN 128 

char *
ixl_aq_speed_to_str(enum i40e_aq_link_speed link_speed)
{
	int index;

	char *speeds[] = {
		"Unknown",
		"100 Mbps",
		"1 Gbps",
		"10 Gbps",
		"40 Gbps",
		"20 Gbps",
		"25 Gbps",
	};

	switch (link_speed) {
	case I40E_LINK_SPEED_100MB:
		index = 1;
		break;
	case I40E_LINK_SPEED_1GB:
		index = 2;
		break;
	case I40E_LINK_SPEED_10GB:
		index = 3;
		break;
	case I40E_LINK_SPEED_40GB:
		index = 4;
		break;
	case I40E_LINK_SPEED_20GB:
		index = 5;
		break;
	case I40E_LINK_SPEED_25GB:
		index = 6;
		break;
	case I40E_LINK_SPEED_UNKNOWN:
	default:
		index = 0;
		break;
	}

	return speeds[index];
}