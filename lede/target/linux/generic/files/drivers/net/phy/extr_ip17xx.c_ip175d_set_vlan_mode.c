#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct ip17xx_state {TYPE_1__* ports; scalar_t__ vlan_enabled; } ;
struct TYPE_2__ {scalar_t__ pvid; } ;

/* Variables and functions */
 int EIO ; 
 int ip175d_update_state (struct ip17xx_state*) ; 
 int ip_phy_write_masked (struct ip17xx_state*,int,int,int,int) ; 

__attribute__((used)) static int ip175d_set_vlan_mode(struct ip17xx_state *state)
{
	int i;
	int err = 0;

	if (state->vlan_enabled) {
		// VLAN classification rules: tag-based VLANs, use VID to classify,
		// drop packets that cannot be classified.
		err |= ip_phy_write_masked(state, 22, 0, 0x3fff, 0x003f);

		// Ingress rules: CFI=1 dropped, null VID is untagged, VID=1 passed,
		// VID=0xfff discarded, admin both tagged and untagged, ingress
		// filters enabled.
		err |= ip_phy_write_masked(state, 22, 1, 0x0fff, 0x0c3f);

		// Egress rules: IGMP processing off, keep VLAN header off
		err |= ip_phy_write_masked(state, 22, 2, 0x0fff, 0x0000);
	} else {
		// VLAN classification rules: everything off & clear table
		err |= ip_phy_write_masked(state, 22, 0, 0xbfff, 0x8000);

		// Ingress and egress rules: set to defaults
		err |= ip_phy_write_masked(state, 22, 1, 0x0fff, 0x0c3f);
		err |= ip_phy_write_masked(state, 22, 2, 0x0fff, 0x0000);
	}

	// Reset default VLAN for each port to 0
	for (i = 0; i < 6; i++)
		state->ports[i].pvid = 0;

	err |= ip175d_update_state(state);

	return (err ? -EIO : 0);
}