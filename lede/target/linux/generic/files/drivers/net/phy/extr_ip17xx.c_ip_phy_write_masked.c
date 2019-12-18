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
struct ip17xx_state {int dummy; } ;

/* Variables and functions */
 int ip_phy_read (struct ip17xx_state*,int,int) ; 
 int ip_phy_write (struct ip17xx_state*,int,int,int) ; 

__attribute__((used)) static int ip_phy_write_masked(struct ip17xx_state *state, int port, int reg, unsigned int mask, unsigned int data)
{
	int val = ip_phy_read(state, port, reg);
	if (val < 0)
		return 0;
	return ip_phy_write(state, port, reg, (val & ~mask) | data);
}