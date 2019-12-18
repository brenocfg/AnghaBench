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
typedef  int u32 ;
struct ar8xxx_priv {int* vlan_id; size_t* pvid; int* port_vlan_prio; scalar_t__ vlan; } ;

/* Variables and functions */
 int AR8216_IN_PORT_ONLY ; 
 int AR8216_IN_SECURE ; 
 int AR8216_PORT_STATE_FORWARD ; 
 int AR8327_PORT_LOOKUP_IN_MODE_S ; 
 int AR8327_PORT_LOOKUP_LEARN ; 
 int AR8327_PORT_LOOKUP_STATE_S ; 
 int AR8327_PORT_VLAN0_DEF_CPRI_S ; 
 int AR8327_PORT_VLAN0_DEF_CVID_S ; 
 int AR8327_PORT_VLAN0_DEF_SPRI_S ; 
 int AR8327_PORT_VLAN0_DEF_SVID_S ; 
 int AR8327_PORT_VLAN1_OUT_MODE_S ; 
 int AR8327_PORT_VLAN1_OUT_MODE_UNMOD ; 
 int AR8327_PORT_VLAN1_OUT_MODE_UNTOUCH ; 
 int AR8327_PORT_VLAN1_PORT_VLAN_PROP ; 
 int AR8327_PORT_VLAN1_VLAN_PRI_PROP ; 
 int /*<<< orphan*/  AR8327_REG_PORT_LOOKUP (int) ; 
 int /*<<< orphan*/  AR8327_REG_PORT_VLAN0 (int) ; 
 int /*<<< orphan*/  AR8327_REG_PORT_VLAN1 (int) ; 
 int /*<<< orphan*/  ar8xxx_write (struct ar8xxx_priv*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
ar8327_setup_port(struct ar8xxx_priv *priv, int port, u32 members)
{
	u32 t;
	u32 egress, ingress;
	u32 pvid = priv->vlan_id[priv->pvid[port]];

	if (priv->vlan) {
		egress = AR8327_PORT_VLAN1_OUT_MODE_UNMOD;
		ingress = AR8216_IN_SECURE;
	} else {
		egress = AR8327_PORT_VLAN1_OUT_MODE_UNTOUCH;
		ingress = AR8216_IN_PORT_ONLY;
	}

	t = pvid << AR8327_PORT_VLAN0_DEF_SVID_S;
	t |= pvid << AR8327_PORT_VLAN0_DEF_CVID_S;
	if (priv->vlan && priv->port_vlan_prio[port]) {
		u32 prio = priv->port_vlan_prio[port];

		t |= prio << AR8327_PORT_VLAN0_DEF_SPRI_S;
		t |= prio << AR8327_PORT_VLAN0_DEF_CPRI_S;
	}
	ar8xxx_write(priv, AR8327_REG_PORT_VLAN0(port), t);

	t = AR8327_PORT_VLAN1_PORT_VLAN_PROP;
	t |= egress << AR8327_PORT_VLAN1_OUT_MODE_S;
	if (priv->vlan && priv->port_vlan_prio[port])
		t |= AR8327_PORT_VLAN1_VLAN_PRI_PROP;

	ar8xxx_write(priv, AR8327_REG_PORT_VLAN1(port), t);

	t = members;
	t |= AR8327_PORT_LOOKUP_LEARN;
	t |= ingress << AR8327_PORT_LOOKUP_IN_MODE_S;
	t |= AR8216_PORT_STATE_FORWARD << AR8327_PORT_LOOKUP_STATE_S;
	ar8xxx_write(priv, AR8327_REG_PORT_LOOKUP(port), t);
}