#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int u16 ;
struct TYPE_7__ {int func; } ;
struct TYPE_6__ {int type; } ;
struct TYPE_8__ {TYPE_2__ bus; TYPE_1__ mac; } ;
struct adapter {int wol; TYPE_3__ hw; void* has_amt; int /*<<< orphan*/  has_manage; } ;
typedef  int /*<<< orphan*/  if_ctx_t ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
#define  E1000_DEV_ID_82546EB_FIBER 161 
#define  E1000_DEV_ID_82546GB_FIBER 160 
#define  E1000_DEV_ID_82546GB_PCIE 159 
#define  E1000_DEV_ID_82546GB_QUAD_COPPER_KSP3 158 
#define  E1000_DEV_ID_82571EB_FIBER 157 
#define  E1000_DEV_ID_82571EB_QUAD_COPPER 156 
#define  E1000_DEV_ID_82571EB_QUAD_COPPER_LP 155 
#define  E1000_DEV_ID_82571EB_QUAD_FIBER 154 
 int E1000_READ_REG (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  E1000_STATUS ; 
 int E1000_STATUS_FUNC_1 ; 
 int /*<<< orphan*/  E1000_WUC ; 
 int E1000_WUC_APME ; 
 int E1000_WUFC_MAG ; 
 int E1000_WUFC_MC ; 
 int EM_82544_APME ; 
 int EM_EEPROM_APME ; 
 int /*<<< orphan*/  NVM_INIT_CONTROL2_REG ; 
 int /*<<< orphan*/  NVM_INIT_CONTROL3_PORT_A ; 
 int /*<<< orphan*/  NVM_INIT_CONTROL3_PORT_B ; 
 void* TRUE ; 
#define  e1000_80003es2lan 153 
#define  e1000_82542 152 
#define  e1000_82543 151 
#define  e1000_82544 150 
#define  e1000_82546 149 
#define  e1000_82546_rev_3 148 
#define  e1000_82571 147 
#define  e1000_82572 146 
#define  e1000_82573 145 
#define  e1000_82575 144 
#define  e1000_82576 143 
#define  e1000_82580 142 
#define  e1000_82583 141 
 int /*<<< orphan*/  e1000_enable_mng_pass_thru (TYPE_3__*) ; 
#define  e1000_i210 140 
#define  e1000_i211 139 
#define  e1000_i350 138 
#define  e1000_i354 137 
#define  e1000_ich10lan 136 
#define  e1000_ich8lan 135 
#define  e1000_ich9lan 134 
#define  e1000_pch2lan 133 
#define  e1000_pch_lpt 132 
#define  e1000_pch_spt 131 
#define  e1000_pchlan 130 
 int /*<<< orphan*/  e1000_read_nvm (TYPE_3__*,int /*<<< orphan*/ ,int,int*) ; 
#define  e1000_vfadapt 129 
#define  e1000_vfadapt_i350 128 
 int global_quad_port_a ; 
 int /*<<< orphan*/  iflib_get_dev (int /*<<< orphan*/ ) ; 
 struct adapter* iflib_get_softc (int /*<<< orphan*/ ) ; 
 int pci_get_device (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
em_get_wakeup(if_ctx_t ctx)
{
	struct adapter *adapter = iflib_get_softc(ctx);
	device_t dev = iflib_get_dev(ctx);
	u16 eeprom_data = 0, device_id, apme_mask;

	adapter->has_manage = e1000_enable_mng_pass_thru(&adapter->hw);
	apme_mask = EM_EEPROM_APME;

	switch (adapter->hw.mac.type) {
	case e1000_82542:
	case e1000_82543:
		break;
	case e1000_82544:
		e1000_read_nvm(&adapter->hw,
		    NVM_INIT_CONTROL2_REG, 1, &eeprom_data);
		apme_mask = EM_82544_APME;
		break;
	case e1000_82546:
	case e1000_82546_rev_3:
		if (adapter->hw.bus.func == 1) {
			e1000_read_nvm(&adapter->hw,
			    NVM_INIT_CONTROL3_PORT_B, 1, &eeprom_data);
			break;
		} else
			e1000_read_nvm(&adapter->hw,
			    NVM_INIT_CONTROL3_PORT_A, 1, &eeprom_data);
		break;
	case e1000_82573:
	case e1000_82583:
		adapter->has_amt = TRUE;
		/* FALLTHROUGH */
	case e1000_82571:
	case e1000_82572:
	case e1000_80003es2lan:
		if (adapter->hw.bus.func == 1) {
			e1000_read_nvm(&adapter->hw,
			    NVM_INIT_CONTROL3_PORT_B, 1, &eeprom_data);
			break;
		} else
			e1000_read_nvm(&adapter->hw,
			    NVM_INIT_CONTROL3_PORT_A, 1, &eeprom_data);
		break;
	case e1000_ich8lan:
	case e1000_ich9lan:
	case e1000_ich10lan:
	case e1000_pchlan:
	case e1000_pch2lan:
	case e1000_pch_lpt:
	case e1000_pch_spt:
	case e1000_82575:	/* listing all igb devices */
	case e1000_82576:
	case e1000_82580:
	case e1000_i350:
	case e1000_i354:
	case e1000_i210:
	case e1000_i211:
	case e1000_vfadapt:
	case e1000_vfadapt_i350:
		apme_mask = E1000_WUC_APME;
		adapter->has_amt = TRUE;
		eeprom_data = E1000_READ_REG(&adapter->hw, E1000_WUC);
		break;
	default:
		e1000_read_nvm(&adapter->hw,
		    NVM_INIT_CONTROL3_PORT_A, 1, &eeprom_data);
		break;
	}
	if (eeprom_data & apme_mask)
		adapter->wol = (E1000_WUFC_MAG | E1000_WUFC_MC);
	/*
	 * We have the eeprom settings, now apply the special cases
	 * where the eeprom may be wrong or the board won't support
	 * wake on lan on a particular port
	 */
	device_id = pci_get_device(dev);
	switch (device_id) {
	case E1000_DEV_ID_82546GB_PCIE:
		adapter->wol = 0;
		break;
	case E1000_DEV_ID_82546EB_FIBER:
	case E1000_DEV_ID_82546GB_FIBER:
		/* Wake events only supported on port A for dual fiber
		 * regardless of eeprom setting */
		if (E1000_READ_REG(&adapter->hw, E1000_STATUS) &
		    E1000_STATUS_FUNC_1)
			adapter->wol = 0;
		break;
	case E1000_DEV_ID_82546GB_QUAD_COPPER_KSP3:
		/* if quad port adapter, disable WoL on all but port A */
		if (global_quad_port_a != 0)
			adapter->wol = 0;
		/* Reset for multiple quad port adapters */
		if (++global_quad_port_a == 4)
			global_quad_port_a = 0;
		break;
	case E1000_DEV_ID_82571EB_FIBER:
		/* Wake events only supported on port A for dual fiber
		 * regardless of eeprom setting */
		if (E1000_READ_REG(&adapter->hw, E1000_STATUS) &
		    E1000_STATUS_FUNC_1)
			adapter->wol = 0;
		break;
	case E1000_DEV_ID_82571EB_QUAD_COPPER:
	case E1000_DEV_ID_82571EB_QUAD_FIBER:
	case E1000_DEV_ID_82571EB_QUAD_COPPER_LP:
		/* if quad port adapter, disable WoL on all but port A */
		if (global_quad_port_a != 0)
			adapter->wol = 0;
		/* Reset for multiple quad port adapters */
		if (++global_quad_port_a == 4)
			global_quad_port_a = 0;
		break;
	}
	return;
}