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
typedef  scalar_t__ u8 ;
typedef  int u16 ;
struct adm6996_priv {int* vlan_id; scalar_t__* vlan_table; scalar_t__* vlan_tagged; } ;

/* Variables and functions */
 int ADM_NUM_VLANS ; 
 int /*<<< orphan*/  ADM_VLAN_FILT_H (int) ; 
 int /*<<< orphan*/  ADM_VLAN_FILT_L (int) ; 
 int ADM_VLAN_FILT_MEMBER (scalar_t__) ; 
 int ADM_VLAN_FILT_TAGGED (scalar_t__) ; 
 int ADM_VLAN_FILT_VALID ; 
 int ADM_VLAN_FILT_VID (int) ; 
 int /*<<< orphan*/  w16 (struct adm6996_priv*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
adm6996_apply_vlan_filters(struct adm6996_priv *priv)
{
	u8 ports, tagged;
	u16 vid, reg;
	int i;

	for (i = 0; i < ADM_NUM_VLANS; i++) {
		vid = priv->vlan_id[i];
		ports = priv->vlan_table[i];
		tagged = priv->vlan_tagged[i];

		if (ports == 0) {
			/* Disable VLAN entry */
			w16(priv, ADM_VLAN_FILT_H(i), 0);
			w16(priv, ADM_VLAN_FILT_L(i), 0);
			continue;
		}

		reg = ADM_VLAN_FILT_MEMBER(ports);
		reg |= ADM_VLAN_FILT_TAGGED(tagged);
		w16(priv, ADM_VLAN_FILT_L(i), reg);
		reg = ADM_VLAN_FILT_VALID | ADM_VLAN_FILT_VID(vid);
		w16(priv, ADM_VLAN_FILT_H(i), reg);
	}
}