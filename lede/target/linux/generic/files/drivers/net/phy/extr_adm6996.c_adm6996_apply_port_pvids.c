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
typedef  int u16 ;
struct adm6996_priv {scalar_t__ model; int tagged_ports; int /*<<< orphan*/ * pvid; } ;

/* Variables and functions */
 scalar_t__ ADM6996L ; 
 int ADM_NUM_PORTS ; 
 int /*<<< orphan*/  ADM_OTBE_P2_PVID ; 
 int /*<<< orphan*/  ADM_P0_PVID ; 
 int ADM_P0_PVID_VAL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ADM_P1_PVID ; 
 int ADM_P1_PVID_VAL (int /*<<< orphan*/ ) ; 
 int ADM_P2_PVID_MASK ; 
 int ADM_P2_PVID_VAL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ADM_P3_P4_PVID ; 
 int ADM_P3_PVID_VAL (int /*<<< orphan*/ ) ; 
 int ADM_P4_PVID_VAL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ADM_P5_PVID ; 
 int ADM_P5_PVID_VAL (int /*<<< orphan*/ ) ; 
 int ADM_PORTCFG_PVID (int /*<<< orphan*/ ) ; 
 int ADM_PORTCFG_PVID_MASK ; 
 int /*<<< orphan*/ * adm_portcfg ; 
 int r16 (struct adm6996_priv*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  w16 (struct adm6996_priv*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
adm6996_apply_port_pvids(struct adm6996_priv *priv)
{
	u16 reg;
	int i;

	for (i = 0; i < ADM_NUM_PORTS; i++) {
		reg = r16(priv, adm_portcfg[i]);
		reg &= ~(ADM_PORTCFG_PVID_MASK);
		reg |= ADM_PORTCFG_PVID(priv->pvid[i]);
		if (priv->model == ADM6996L) {
			if (priv->tagged_ports & (1 << i))
				reg |= (1 << 4);
			else
				reg &= ~(1 << 4);
		}
		w16(priv, adm_portcfg[i], reg);
	}

	w16(priv, ADM_P0_PVID, ADM_P0_PVID_VAL(priv->pvid[0]));
	w16(priv, ADM_P1_PVID, ADM_P1_PVID_VAL(priv->pvid[1]));
	reg = r16(priv, ADM_OTBE_P2_PVID);
	reg &= ~(ADM_P2_PVID_MASK);
	reg |= ADM_P2_PVID_VAL(priv->pvid[2]);
	w16(priv, ADM_OTBE_P2_PVID, reg);
	reg = ADM_P3_PVID_VAL(priv->pvid[3]);
	reg |= ADM_P4_PVID_VAL(priv->pvid[4]);
	w16(priv, ADM_P3_P4_PVID, reg);
	reg = r16(priv, ADM_P5_PVID);
	reg &= ~(ADM_P2_PVID_MASK);
	reg |= ADM_P5_PVID_VAL(priv->pvid[5]);
	w16(priv, ADM_P5_PVID, reg);
}