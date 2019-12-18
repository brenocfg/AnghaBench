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
typedef  int /*<<< orphan*/  u16 ;
struct adm6996_priv {scalar_t__* vlan_table; } ;

/* Variables and functions */
 int ADM_NUM_VLANS ; 
 int /*<<< orphan*/  ADM_VLAN_FILT (scalar_t__) ; 
 int /*<<< orphan*/  ADM_VLAN_MAP (int) ; 
 int /*<<< orphan*/  w16 (struct adm6996_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
adm6996_apply_vlan_filters_6996l(struct adm6996_priv *priv)
{
	u8 ports;
	u16 reg;
	int i;

	for (i = 0; i < ADM_NUM_VLANS; i++) {
		ports = priv->vlan_table[i];

		if (ports == 0) {
			/* Disable VLAN entry */
			w16(priv, ADM_VLAN_MAP(i), 0);
			continue;
		} else {
			reg = ADM_VLAN_FILT(ports);
			w16(priv, ADM_VLAN_MAP(i), reg);
		}
	}
}