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
struct mt753x_port_cfg {int speed; scalar_t__ duplex; } ;
struct gsw_mt753x {int /*<<< orphan*/  dev; } ;
typedef  int /*<<< orphan*/  ktime_t ;

/* Variables and functions */
 int EINVAL ; 
 int ETIMEDOUT ; 
#define  MAC_SPD_1000 129 
#define  MAC_SPD_2500 128 
 int MT753X_NUM_PORTS ; 
 int /*<<< orphan*/  PCS_CONTROL_1 (int) ; 
 int /*<<< orphan*/  PHYA_CTRL_SIGNAL3 (int) ; 
 int PHYA_PWD ; 
 int /*<<< orphan*/  QPHY_PWR_STATE_CTRL (int) ; 
 int RG_TPHY_SPEED_1000 ; 
 int RG_TPHY_SPEED_2500 ; 
 int RG_TPHY_SPEED_M ; 
 int RG_TPHY_SPEED_S ; 
 int SGMII_AN_ENABLE ; 
 int SGMII_IF_MODE_ADVERT_AN ; 
 int SGMII_IF_MODE_FORCE_DUPLEX ; 
 int SGMII_IF_MODE_FORCE_SPEED_1000 ; 
 int SGMII_IF_MODE_FORCE_SPEED_M ; 
 int SGMII_IF_MODE_FORCE_SPEED_S ; 
 int SGMII_LINK_STATUS ; 
 int /*<<< orphan*/  SGMII_MODE (int) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ ,char*,int,...) ; 
 int /*<<< orphan*/  ktime_add_us (int /*<<< orphan*/ ,int) ; 
 scalar_t__ ktime_compare (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ktime_get () ; 
 int mt753x_reg_read (struct gsw_mt753x*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mt753x_reg_write (struct gsw_mt753x*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int mt7531_set_port_sgmii_force_mode(struct gsw_mt753x *gsw, u32 port,
					    struct mt753x_port_cfg *port_cfg)
{
	u32 speed, port_base, val;
	ktime_t timeout;
	u32 timeout_us;

	if (port < 5 || port >= MT753X_NUM_PORTS) {
		dev_info(gsw->dev, "port %d is not a SGMII port\n", port);
		return -EINVAL;
	}

	port_base = port - 5;

	switch (port_cfg->speed) {
	case MAC_SPD_1000:
		speed = RG_TPHY_SPEED_1000;
		break;
	case MAC_SPD_2500:
		speed = RG_TPHY_SPEED_2500;
		break;
	default:
		dev_info(gsw->dev, "invalid SGMII speed idx %d for port %d\n",
			 port_cfg->speed, port);

		speed = RG_TPHY_SPEED_1000;
	}

	/* Step 1: Speed select register setting */
	val = mt753x_reg_read(gsw, PHYA_CTRL_SIGNAL3(port_base));
	val &= ~RG_TPHY_SPEED_M;
	val |= speed << RG_TPHY_SPEED_S;
	mt753x_reg_write(gsw, PHYA_CTRL_SIGNAL3(port_base), val);

	/* Step 2 : Disable AN */
	val = mt753x_reg_read(gsw, PCS_CONTROL_1(port_base));
	val &= ~SGMII_AN_ENABLE;
	mt753x_reg_write(gsw, PCS_CONTROL_1(port_base), val);

	/* Step 3: SGMII force mode setting */
	val = mt753x_reg_read(gsw, SGMII_MODE(port_base));
	val &= ~SGMII_IF_MODE_ADVERT_AN;
	val &= ~SGMII_IF_MODE_FORCE_SPEED_M;
	val |= SGMII_IF_MODE_FORCE_SPEED_1000 << SGMII_IF_MODE_FORCE_SPEED_S;
	val |= SGMII_IF_MODE_FORCE_DUPLEX;
	/* For sgmii force mode, 0 is full duplex and 1 is half duplex */
	if (port_cfg->duplex)
		val &= ~SGMII_IF_MODE_FORCE_DUPLEX;

	mt753x_reg_write(gsw, SGMII_MODE(port_base), val);

	/* Step 4: XXX: Disable Link partner's AN and set force mode */

	/* Step 5: XXX: Special setting for PHYA ==> reserved for flexible */

	/* Step 6 : Release PHYA power down state */
	val = mt753x_reg_read(gsw, QPHY_PWR_STATE_CTRL(port_base));
	val &= ~PHYA_PWD;
	mt753x_reg_write(gsw, QPHY_PWR_STATE_CTRL(port_base), val);

	/* Step 7 : Polling SGMII_LINK_STATUS */
	timeout_us = 2000000;
	timeout = ktime_add_us(ktime_get(), timeout_us);
	while (1) {
		val = mt753x_reg_read(gsw, PCS_CONTROL_1(port_base));
		val &= SGMII_LINK_STATUS;

		if (val)
			break;

		if (ktime_compare(ktime_get(), timeout) > 0)
			return -ETIMEDOUT;
	}

	return 0;
}