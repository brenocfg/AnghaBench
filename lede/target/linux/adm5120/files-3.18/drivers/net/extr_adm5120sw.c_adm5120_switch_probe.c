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
struct platform_device {int dummy; } ;
struct net_device {int /*<<< orphan*/  name; int /*<<< orphan*/  dev_addr; } ;
struct adm5120_if_priv {int vlan_no; int /*<<< orphan*/  port_mask; } ;

/* Variables and functions */
 int CPUP_CONF_CRCP ; 
 int CPUP_CONF_DCPUP ; 
 int CPUP_CONF_DMCP_SHIFT ; 
 int CPUP_CONF_DUNP_SHIFT ; 
 int ENOMEM ; 
 int KSEG1ADDR (int /*<<< orphan*/ ) ; 
 int PHY_CNTL2_AMDIX_SHIFT ; 
 int PHY_CNTL2_DC_SHIFT ; 
 int PHY_CNTL2_PHYR_SHIFT ; 
 int PHY_CNTL2_RMAE ; 
 int PHY_CNTL2_SC_SHIFT ; 
 int PHY_CNTL3_RNT ; 
 int PORT_CONF0_BP_SHIFT ; 
 int PORT_CONF0_EMCP_SHIFT ; 
 int /*<<< orphan*/  RX_RING_SIZE ; 
 int /*<<< orphan*/  SWITCH_INTS_ALL ; 
 int SWITCH_NUM_PORTS ; 
 int SWITCH_PORTS_NOCPU ; 
 int SWITCH_PORTS_PHY ; 
 int /*<<< orphan*/  SWITCH_REG_CPUP_CONF ; 
 int /*<<< orphan*/  SWITCH_REG_PHY_CNTL2 ; 
 int /*<<< orphan*/  SWITCH_REG_PHY_CNTL3 ; 
 int /*<<< orphan*/  SWITCH_REG_PORT_CONF0 ; 
 int /*<<< orphan*/  SWITCH_REG_PRI_CNTL ; 
 int /*<<< orphan*/  SWITCH_REG_RHDA ; 
 int /*<<< orphan*/  SWITCH_REG_RLDA ; 
 int /*<<< orphan*/  SWITCH_REG_SHDA ; 
 int /*<<< orphan*/  SWITCH_REG_SLDA ; 
 int /*<<< orphan*/  SW_ERR (char*) ; 
 int /*<<< orphan*/  SW_INFO (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  TX_RING_SIZE ; 
 struct net_device** adm5120_devs ; 
 int /*<<< orphan*/ * adm5120_eth_macs ; 
 int /*<<< orphan*/  adm5120_eth_num_ports ; 
 int /*<<< orphan*/ * adm5120_eth_vlans ; 
 struct net_device* adm5120_if_alloc () ; 
 int /*<<< orphan*/  adm5120_nrdevs ; 
 int /*<<< orphan*/  adm5120_set_vlan (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  adm5120_switch_cleanup () ; 
 int adm5120_switch_rx_ring_alloc () ; 
 int /*<<< orphan*/  adm5120_switch_rx_ring_reset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int adm5120_switch_tx_ring_alloc () ; 
 int /*<<< orphan*/  adm5120_switch_tx_ring_reset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  adm5120_write_mac (struct net_device*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 struct adm5120_if_priv* netdev_priv (struct net_device*) ; 
 int register_netdev (struct net_device*) ; 
 int /*<<< orphan*/  rxl_descs ; 
 int /*<<< orphan*/  rxl_skbuff ; 
 int /*<<< orphan*/  sw_int_ack (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sw_int_mask (int /*<<< orphan*/ ) ; 
 int sw_read_reg (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sw_write_reg (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  txl_descs ; 
 int /*<<< orphan*/  txl_skbuff ; 

__attribute__((used)) static int adm5120_switch_probe(struct platform_device *pdev)
{
	u32 t;
	int i, err;

	adm5120_nrdevs = adm5120_eth_num_ports;

	t = CPUP_CONF_DCPUP | CPUP_CONF_CRCP |
		SWITCH_PORTS_NOCPU << CPUP_CONF_DUNP_SHIFT |
		SWITCH_PORTS_NOCPU << CPUP_CONF_DMCP_SHIFT ;
	sw_write_reg(SWITCH_REG_CPUP_CONF, t);

	t = (SWITCH_PORTS_NOCPU << PORT_CONF0_EMCP_SHIFT) |
		(SWITCH_PORTS_NOCPU << PORT_CONF0_BP_SHIFT) |
		(SWITCH_PORTS_NOCPU);
	sw_write_reg(SWITCH_REG_PORT_CONF0, t);

	/* setup ports to Autoneg/100M/Full duplex/Auto MDIX */
	t =  SWITCH_PORTS_PHY |
		(SWITCH_PORTS_PHY << PHY_CNTL2_SC_SHIFT) |
		(SWITCH_PORTS_PHY << PHY_CNTL2_DC_SHIFT) |
		(SWITCH_PORTS_PHY << PHY_CNTL2_PHYR_SHIFT) |
		(SWITCH_PORTS_PHY << PHY_CNTL2_AMDIX_SHIFT) |
		PHY_CNTL2_RMAE;
	sw_write_reg(SWITCH_REG_PHY_CNTL2, t);

	t = sw_read_reg(SWITCH_REG_PHY_CNTL3);
	t |= PHY_CNTL3_RNT;
	sw_write_reg(SWITCH_REG_PHY_CNTL3, t);

	/* Force all the packets from all ports are low priority */
	sw_write_reg(SWITCH_REG_PRI_CNTL, 0);

	sw_int_mask(SWITCH_INTS_ALL);
	sw_int_ack(SWITCH_INTS_ALL);

	err = adm5120_switch_rx_ring_alloc();
	if (err)
		goto err;

	err = adm5120_switch_tx_ring_alloc();
	if (err)
		goto err;

	adm5120_switch_tx_ring_reset(txl_descs, txl_skbuff, TX_RING_SIZE);
	adm5120_switch_rx_ring_reset(rxl_descs, rxl_skbuff, RX_RING_SIZE);

	sw_write_reg(SWITCH_REG_SHDA, 0);
	sw_write_reg(SWITCH_REG_SLDA, KSEG1ADDR(txl_descs));
	sw_write_reg(SWITCH_REG_RHDA, 0);
	sw_write_reg(SWITCH_REG_RLDA, KSEG1ADDR(rxl_descs));

	for (i = 0; i < SWITCH_NUM_PORTS; i++) {
		struct net_device *dev;
		struct adm5120_if_priv *priv;

		dev = adm5120_if_alloc();
		if (!dev) {
			err = -ENOMEM;
			goto err;
		}

		adm5120_devs[i] = dev;
		priv = netdev_priv(dev);

		priv->vlan_no = i;
		priv->port_mask = adm5120_eth_vlans[i];

		memcpy(dev->dev_addr, adm5120_eth_macs[i], 6);
		adm5120_write_mac(dev);

		err = register_netdev(dev);
		if (err) {
			SW_INFO("%s register failed, error=%d\n",
					dev->name, err);
			goto err;
		}
	}

	/* setup vlan/port mapping after devs are filled up */
	adm5120_set_vlan(adm5120_eth_vlans);

	/* enable CPU port */
	t = sw_read_reg(SWITCH_REG_CPUP_CONF);
	t &= ~CPUP_CONF_DCPUP;
	sw_write_reg(SWITCH_REG_CPUP_CONF, t);

	return 0;

err:
	adm5120_switch_cleanup();

	SW_ERR("init failed\n");
	return err;
}