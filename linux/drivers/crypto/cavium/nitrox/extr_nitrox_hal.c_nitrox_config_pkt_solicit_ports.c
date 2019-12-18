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
struct nitrox_device {int nr_queues; } ;

/* Variables and functions */
 int /*<<< orphan*/  config_pkt_solicit_port (struct nitrox_device*,int) ; 

void nitrox_config_pkt_solicit_ports(struct nitrox_device *ndev)
{
	int i;

	for (i = 0; i < ndev->nr_queues; i++)
		config_pkt_solicit_port(ndev, i);
}