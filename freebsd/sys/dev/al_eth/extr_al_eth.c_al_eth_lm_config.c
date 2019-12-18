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
struct al_eth_lm_init_params {int sfp_detection; int rx_equal; int static_values; int kr_fec_enable; int /*<<< orphan*/  retimer_channel; int /*<<< orphan*/  retimer_i2c_addr; int /*<<< orphan*/  retimer_bus_id; int /*<<< orphan*/  retimer_exist; struct al_eth_adapter* i2c_context; int /*<<< orphan*/  link_training; void* default_mode; int /*<<< orphan*/  sfp_i2c_addr; int /*<<< orphan*/  sfp_bus_id; int /*<<< orphan*/  lane; int /*<<< orphan*/ * serdes_obj; int /*<<< orphan*/ * adapter; int /*<<< orphan*/  member_0; } ;
struct TYPE_2__ {int /*<<< orphan*/  channel; int /*<<< orphan*/  i2c_addr; int /*<<< orphan*/  bus_id; int /*<<< orphan*/  exist; } ;
struct al_eth_adapter {int sfp_detection_needed; int mac_mode; int /*<<< orphan*/  lm_context; TYPE_1__ retimer; int /*<<< orphan*/  dont_override_serdes; int /*<<< orphan*/  lt_en; int /*<<< orphan*/  an_en; int /*<<< orphan*/  i2c_adapter_id; int /*<<< orphan*/  serdes_lane; int /*<<< orphan*/  serdes_obj; int /*<<< orphan*/  hal_adapter; } ;

/* Variables and functions */
 void* AL_ETH_LM_MODE_10G_DA ; 
 void* AL_ETH_LM_MODE_10G_OPTIC ; 
 void* AL_ETH_LM_MODE_1G ; 
#define  AL_ETH_MAC_MODE_10GbE_Serial 129 
#define  AL_ETH_MAC_MODE_SGMII 128 
 int /*<<< orphan*/  SFP_I2C_ADDR ; 
 int /*<<< orphan*/  al_eth_lm_init (int /*<<< orphan*/ *,struct al_eth_lm_init_params*) ; 

__attribute__((used)) static void
al_eth_lm_config(struct al_eth_adapter *adapter)
{
	struct al_eth_lm_init_params params = {0};

	params.adapter = &adapter->hal_adapter;
	params.serdes_obj = &adapter->serdes_obj;
	params.lane = adapter->serdes_lane;
	params.sfp_detection = adapter->sfp_detection_needed;
	if (adapter->sfp_detection_needed == true) {
		params.sfp_bus_id = adapter->i2c_adapter_id;
		params.sfp_i2c_addr = SFP_I2C_ADDR;
	}

	if (adapter->sfp_detection_needed == false) {
		switch (adapter->mac_mode) {
		case AL_ETH_MAC_MODE_10GbE_Serial:
			if ((adapter->lt_en != 0) && (adapter->an_en != 0))
				params.default_mode = AL_ETH_LM_MODE_10G_DA;
			else
				params.default_mode = AL_ETH_LM_MODE_10G_OPTIC;
			break;
		case AL_ETH_MAC_MODE_SGMII:
			params.default_mode = AL_ETH_LM_MODE_1G;
			break;
		default:
			params.default_mode = AL_ETH_LM_MODE_10G_DA;
		}
	} else
		params.default_mode = AL_ETH_LM_MODE_10G_DA;

	params.link_training = adapter->lt_en;
	params.rx_equal = true;
	params.static_values = !adapter->dont_override_serdes;
	params.i2c_context = adapter;
	params.kr_fec_enable = false;

	params.retimer_exist = adapter->retimer.exist;
	params.retimer_bus_id = adapter->retimer.bus_id;
	params.retimer_i2c_addr = adapter->retimer.i2c_addr;
	params.retimer_channel = adapter->retimer.channel;

	al_eth_lm_init(&adapter->lm_context, &params);
}