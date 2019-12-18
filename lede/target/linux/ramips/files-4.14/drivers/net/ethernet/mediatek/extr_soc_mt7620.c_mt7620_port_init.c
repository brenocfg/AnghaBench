#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct mt7620_gsw {scalar_t__ port4; int /*<<< orphan*/  autopoll; } ;
struct fe_priv {int* link; TYPE_2__* phy; int /*<<< orphan*/  mii_bus; int /*<<< orphan*/  dev; TYPE_1__* soc; } ;
struct device_node {int /*<<< orphan*/  name; } ;
typedef  int /*<<< orphan*/  __be32 ;
struct TYPE_4__ {int* speed; int* duplex; scalar_t__* phy_node; int /*<<< orphan*/ ** phy_fixed; } ;
struct TYPE_3__ {scalar_t__ swpriv; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIT (int) ; 
 int /*<<< orphan*/  GSW_REG_PORT_PMCR (int) ; 
#define  PHY_INTERFACE_MODE_MII 133 
#define  PHY_INTERFACE_MODE_RGMII 132 
#define  PHY_INTERFACE_MODE_RMII 131 
 int PMCR_BACKOFF ; 
 int PMCR_BACKPRES ; 
 int PMCR_DUPLEX ; 
 int PMCR_FORCE ; 
 int PMCR_IPG ; 
 int PMCR_LINK ; 
 int PMCR_MAC_MODE ; 
 int PMCR_RX_EN ; 
 int PMCR_RX_FC ; 
 int PMCR_SPEED (int) ; 
 int PMCR_TX_EN ; 
 int PMCR_TX_FC ; 
 scalar_t__ PORT4_EPHY ; 
#define  SPEED_10 130 
#define  SPEED_100 129 
#define  SPEED_1000 128 
 int /*<<< orphan*/  SYSC_REG_CFG1 ; 
 int be32_to_cpu (int /*<<< orphan*/  const) ; 
 void* be32_to_cpup (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  fe_connect_phy_node (struct fe_priv*,scalar_t__) ; 
 scalar_t__ mdiobus_get_phy (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mt7620_auto_poll (struct mt7620_gsw*) ; 
 int /*<<< orphan*/  mtk_switch_w32 (struct mt7620_gsw*,int,int /*<<< orphan*/ ) ; 
 int of_get_phy_mode (struct device_node*) ; 
 void* of_get_property (struct device_node*,char*,int*) ; 
 scalar_t__ of_parse_phandle (struct device_node*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_err (char*,int /*<<< orphan*/ ,...) ; 
 int rt_sysc_r32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rt_sysc_w32 (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void mt7620_port_init(struct fe_priv *priv, struct device_node *np)
{
	struct mt7620_gsw *gsw = (struct mt7620_gsw *)priv->soc->swpriv;
	const __be32 *_id = of_get_property(np, "reg", NULL);
	int phy_mode, size, id;
	int shift = 12;
	u32 val, mask = 0;
	int min = (gsw->port4 == PORT4_EPHY) ? (5) : (4);

	if (!_id || (be32_to_cpu(*_id) < min) || (be32_to_cpu(*_id) > 5)) {
		if (_id)
			pr_err("%s: invalid port id %d\n", np->name,
			       be32_to_cpu(*_id));
		else
			pr_err("%s: invalid port id\n", np->name);
		return;
	}

	id = be32_to_cpu(*_id);

	if (id == 4)
		shift = 14;

	priv->phy->phy_fixed[id] = of_get_property(np, "mediatek,fixed-link",
						   &size);
	if (priv->phy->phy_fixed[id] &&
	    (size != (4 * sizeof(*priv->phy->phy_fixed[id])))) {
		pr_err("%s: invalid fixed link property\n", np->name);
		priv->phy->phy_fixed[id] = NULL;
		return;
	}

	phy_mode = of_get_phy_mode(np);
	switch (phy_mode) {
	case PHY_INTERFACE_MODE_RGMII:
		mask = 0;
		break;
	case PHY_INTERFACE_MODE_MII:
		mask = 1;
		break;
	case PHY_INTERFACE_MODE_RMII:
		mask = 2;
		break;
	default:
		dev_err(priv->dev, "port %d - invalid phy mode\n", id);
		return;
	}

	priv->phy->phy_node[id] = of_parse_phandle(np, "phy-handle", 0);
	if (!priv->phy->phy_node[id] && !priv->phy->phy_fixed[id])
		return;

	val = rt_sysc_r32(SYSC_REG_CFG1);
	val &= ~(3 << shift);
	val |= mask << shift;
	rt_sysc_w32(val, SYSC_REG_CFG1);

	if (priv->phy->phy_fixed[id]) {
		const __be32 *link = priv->phy->phy_fixed[id];
		int tx_fc, rx_fc;
		u32 val = 0;

		priv->phy->speed[id] = be32_to_cpup(link++);
		tx_fc = be32_to_cpup(link++);
		rx_fc = be32_to_cpup(link++);
		priv->phy->duplex[id] = be32_to_cpup(link++);
		priv->link[id] = 1;

		switch (priv->phy->speed[id]) {
		case SPEED_10:
			val = 0;
			break;
		case SPEED_100:
			val = 1;
			break;
		case SPEED_1000:
			val = 2;
			break;
		default:
			dev_err(priv->dev, "invalid link speed: %d\n",
				priv->phy->speed[id]);
			priv->phy->phy_fixed[id] = 0;
			return;
		}
		val = PMCR_SPEED(val);
		val |= PMCR_LINK | PMCR_BACKPRES | PMCR_BACKOFF | PMCR_RX_EN |
			PMCR_TX_EN | PMCR_FORCE | PMCR_MAC_MODE | PMCR_IPG;
		if (tx_fc)
			val |= PMCR_TX_FC;
		if (rx_fc)
			val |= PMCR_RX_FC;
		if (priv->phy->duplex[id])
			val |= PMCR_DUPLEX;
		mtk_switch_w32(gsw, val, GSW_REG_PORT_PMCR(id));
		dev_info(priv->dev, "using fixed link parameters\n");
		return;
	}

	if (priv->phy->phy_node[id] && mdiobus_get_phy(priv->mii_bus, id)) {
		u32 val = PMCR_BACKPRES | PMCR_BACKOFF | PMCR_RX_EN |
			PMCR_TX_EN |  PMCR_MAC_MODE | PMCR_IPG;

		mtk_switch_w32(gsw, val, GSW_REG_PORT_PMCR(id));
		fe_connect_phy_node(priv, priv->phy->phy_node[id]);
		gsw->autopoll |= BIT(id);
		mt7620_auto_poll(gsw);
		return;
	}
}