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
 int NUM_PORTS ; 
 int REG_PHY (int) ; 

__attribute__((used)) static int mv88e6063_port_to_phy_addr(int port)
{
	if (port >= 0 && port <= NUM_PORTS)
		return REG_PHY(port);
	return -1;
}