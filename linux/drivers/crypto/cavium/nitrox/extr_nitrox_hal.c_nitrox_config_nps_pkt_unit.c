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
struct nitrox_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  enable_nps_pkt_interrupts (struct nitrox_device*) ; 
 int /*<<< orphan*/  nitrox_config_pkt_input_rings (struct nitrox_device*) ; 
 int /*<<< orphan*/  nitrox_config_pkt_solicit_ports (struct nitrox_device*) ; 

void nitrox_config_nps_pkt_unit(struct nitrox_device *ndev)
{
	/* config input and solicit ports */
	nitrox_config_pkt_input_rings(ndev);
	nitrox_config_pkt_solicit_ports(ndev);

	/* enable nps packet interrupts */
	enable_nps_pkt_interrupts(ndev);
}