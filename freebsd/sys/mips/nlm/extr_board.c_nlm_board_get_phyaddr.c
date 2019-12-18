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

__attribute__((used)) static void
nlm_board_get_phyaddr(int block, int port, int *phyaddr)
{
	switch (block) {
	case 0: switch (port) {
		case 0: *phyaddr = 4; break;
		case 1: *phyaddr = 7; break;
		case 2: *phyaddr = 6; break;
		case 3: *phyaddr = 5; break;
		}
		break;
	case 1: switch (port) {
		case 0: *phyaddr = 8; break;
		case 1: *phyaddr = 11; break;
		case 2: *phyaddr = 10; break;
		case 3: *phyaddr = 9; break;
		}
		break;
	case 2: switch (port) {
		case 0: *phyaddr = 0; break;
		case 1: *phyaddr = 3; break;
		case 2: *phyaddr = 2; break;
		case 3: *phyaddr = 1; break;
		}
		break;
	case 3: switch (port) {
		case 0: *phyaddr = 12; break;
		case 1: *phyaddr = 15; break;
		case 2: *phyaddr = 14; break;
		case 3: *phyaddr = 13; break;
		}
		break;
	case 4: switch (port) { /* management SGMII */
		case 0: *phyaddr = 16; break;
		case 1: *phyaddr = 17; break;
		}
		break;
	}
}