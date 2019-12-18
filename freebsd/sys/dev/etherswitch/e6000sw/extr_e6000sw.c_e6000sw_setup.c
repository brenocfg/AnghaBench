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
typedef  int uint32_t ;
typedef  int /*<<< orphan*/  e6000sw_softc_t ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  ATU_CONTROL ; 
 int ATU_CONTROL_AGETIME ; 
 int ATU_CONTROL_AGETIME_MASK ; 
 int /*<<< orphan*/  COUNT_ALL ; 
 int E6000SW_DEFAULT_AGETIME ; 
 int /*<<< orphan*/  MGMT_EN_0x ; 
 int /*<<< orphan*/  MGMT_EN_2x ; 
 int MGMT_EN_ALL ; 
 int /*<<< orphan*/  NO_OPERATION ; 
 int /*<<< orphan*/  REG_GLOBAL ; 
 int /*<<< orphan*/  REG_GLOBAL2 ; 
 int /*<<< orphan*/  SWITCH_GLOBAL_CONTROL2 ; 
 int /*<<< orphan*/  SWITCH_MGMT ; 
 int SWITCH_MGMT_FC_PRI_MASK ; 
 int SWITCH_MGMT_FORCEFLOW ; 
 int SWITCH_MGMT_PRI_MASK ; 
 int SWITCH_MGMT_RSVD2CPU ; 
 int /*<<< orphan*/  e6000sw_atu_flush (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  e6000sw_atu_mac_table (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int e6000sw_readreg (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  e6000sw_set_atustat (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  e6000sw_writereg (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
e6000sw_setup(device_t dev, e6000sw_softc_t *sc)
{
	uint32_t atu_ctrl;

	/* Set aging time. */
	atu_ctrl = e6000sw_readreg(sc, REG_GLOBAL, ATU_CONTROL);
	atu_ctrl &= ~ATU_CONTROL_AGETIME_MASK;
	atu_ctrl |= E6000SW_DEFAULT_AGETIME << ATU_CONTROL_AGETIME;
	e6000sw_writereg(sc, REG_GLOBAL, ATU_CONTROL, atu_ctrl);

	/* Send all with specific mac address to cpu port */
	e6000sw_writereg(sc, REG_GLOBAL2, MGMT_EN_2x, MGMT_EN_ALL);
	e6000sw_writereg(sc, REG_GLOBAL2, MGMT_EN_0x, MGMT_EN_ALL);

	/* Disable Remote Management */
	e6000sw_writereg(sc, REG_GLOBAL, SWITCH_GLOBAL_CONTROL2, 0);

	/* Disable loopback filter and flow control messages */
	e6000sw_writereg(sc, REG_GLOBAL2, SWITCH_MGMT,
	    SWITCH_MGMT_PRI_MASK |
	    (1 << SWITCH_MGMT_RSVD2CPU) |
	    SWITCH_MGMT_FC_PRI_MASK |
	    (1 << SWITCH_MGMT_FORCEFLOW));

	e6000sw_atu_flush(dev, sc, NO_OPERATION);
	e6000sw_atu_mac_table(dev, sc, NULL, NO_OPERATION);
	e6000sw_set_atustat(dev, sc, 0, COUNT_ALL);
}