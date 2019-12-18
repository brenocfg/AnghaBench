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

/* Variables and functions */

__attribute__((used)) static const char *port_phy_state_str(uint8_t phys_state)
{
	switch (phys_state) {
	case 1:  return "SLEEP";
	case 2:  return "POLLING";
	case 3:  return "DISABLED";
	case 4:  return "PORT_CONFIGURATION TRAINNING";
	case 5:  return "LINK_UP";
	case 6:  return "LINK_ERROR_RECOVERY";
	case 7:  return "PHY TEST";
	default: return "invalid physical state";
	}
}