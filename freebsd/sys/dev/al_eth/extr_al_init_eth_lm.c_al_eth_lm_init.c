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
struct al_eth_lm_init_params {scalar_t__ sfp_detection; scalar_t__ retimer_exist; int /*<<< orphan*/  led_config; int /*<<< orphan*/  lm_pause; int /*<<< orphan*/  sfp_detect_force_mode; int /*<<< orphan*/  max_speed; int /*<<< orphan*/  gpio_present; int /*<<< orphan*/  gpio_get; int /*<<< orphan*/  kr_fec_enable; int /*<<< orphan*/  get_random_byte; int /*<<< orphan*/  i2c_context; int /*<<< orphan*/ * i2c_write; int /*<<< orphan*/ * i2c_read; int /*<<< orphan*/  static_values; int /*<<< orphan*/  rx_equal; int /*<<< orphan*/  link_training; int /*<<< orphan*/  default_dac_len; int /*<<< orphan*/  default_mode; int /*<<< orphan*/  retimer_tx_channel; int /*<<< orphan*/  retimer_channel; int /*<<< orphan*/  retimer_i2c_addr; int /*<<< orphan*/  retimer_bus_id; int /*<<< orphan*/  retimer_type; int /*<<< orphan*/  sfp_i2c_addr; int /*<<< orphan*/  sfp_bus_id; int /*<<< orphan*/  lane; int /*<<< orphan*/  serdes_obj; int /*<<< orphan*/  adapter; } ;
struct TYPE_2__ {int selector_field; int /*<<< orphan*/  fec_capability; int /*<<< orphan*/  technology; scalar_t__ next_page; scalar_t__ acknowledge; scalar_t__ remote_fault; scalar_t__ capability; } ;
struct al_eth_lm_context {scalar_t__ sfp_detection; scalar_t__ retimer_exist; int rx_param_dirty; int tx_param_dirty; int /*<<< orphan*/  link_state; scalar_t__ retimer_configured; int /*<<< orphan*/  led_config; int /*<<< orphan*/  lm_pause; int /*<<< orphan*/  sfp_detect_force_mode; int /*<<< orphan*/  max_speed; int /*<<< orphan*/  gpio_present; int /*<<< orphan*/  gpio_get; scalar_t__ serdes_rx_params_valid; scalar_t__ serdes_tx_params_valid; int /*<<< orphan*/  mode; TYPE_1__ local_adv; int /*<<< orphan*/ * i2c_write; int /*<<< orphan*/ * i2c_read; int /*<<< orphan*/  get_random_byte; int /*<<< orphan*/  i2c_context; int /*<<< orphan*/  static_values; int /*<<< orphan*/  rx_equal; int /*<<< orphan*/  link_training; int /*<<< orphan*/  default_dac_len; int /*<<< orphan*/  default_mode; int /*<<< orphan*/  retimer_tx_channel; int /*<<< orphan*/  retimer_channel; int /*<<< orphan*/  retimer_i2c_addr; int /*<<< orphan*/  retimer_bus_id; int /*<<< orphan*/  retimer_type; int /*<<< orphan*/  sfp_i2c_addr; int /*<<< orphan*/  sfp_bus_id; int /*<<< orphan*/  lane; int /*<<< orphan*/  serdes_obj; int /*<<< orphan*/  adapter; } ;

/* Variables and functions */
 int /*<<< orphan*/  AL_ETH_AN_TECH_10GBASE_KR ; 
 int /*<<< orphan*/  AL_ETH_LM_LINK_DOWN ; 
 int /*<<< orphan*/  AL_ETH_LM_MODE_DISCONNECTED ; 
 scalar_t__ FALSE ; 
 int /*<<< orphan*/  al_assert (int) ; 

int
al_eth_lm_init(struct al_eth_lm_context	*lm_context,
    struct al_eth_lm_init_params *params)
{

	lm_context->adapter = params->adapter;
	lm_context->serdes_obj = params->serdes_obj;
	lm_context->lane = params->lane;
	lm_context->sfp_detection = params->sfp_detection;
	lm_context->sfp_bus_id = params->sfp_bus_id;
	lm_context->sfp_i2c_addr = params->sfp_i2c_addr;

	lm_context->retimer_exist = params->retimer_exist;
	lm_context->retimer_type = params->retimer_type;
	lm_context->retimer_bus_id = params->retimer_bus_id;
	lm_context->retimer_i2c_addr = params->retimer_i2c_addr;
	lm_context->retimer_channel = params->retimer_channel;
	lm_context->retimer_tx_channel = params->retimer_tx_channel;

	lm_context->default_mode = params->default_mode;
	lm_context->default_dac_len = params->default_dac_len;
	lm_context->link_training = params->link_training;
	lm_context->rx_equal = params->rx_equal;
	lm_context->static_values = params->static_values;
	lm_context->i2c_read = params->i2c_read;
	lm_context->i2c_write = params->i2c_write;
	lm_context->i2c_context = params->i2c_context;
	lm_context->get_random_byte = params->get_random_byte;

	/* eeprom_read must be provided if sfp_detection is true */
	al_assert((lm_context->sfp_detection == FALSE) ||
	    (lm_context->i2c_read != NULL));

	al_assert((lm_context->retimer_exist == FALSE) ||
	    (lm_context->i2c_write != NULL));

	lm_context->local_adv.selector_field = 1;
	lm_context->local_adv.capability = 0;
	lm_context->local_adv.remote_fault = 0;
	lm_context->local_adv.acknowledge = 0;
	lm_context->local_adv.next_page = 0;
	lm_context->local_adv.technology = AL_ETH_AN_TECH_10GBASE_KR;
	lm_context->local_adv.fec_capability = params->kr_fec_enable;

	lm_context->mode = AL_ETH_LM_MODE_DISCONNECTED;
	lm_context->serdes_tx_params_valid = FALSE;
	lm_context->serdes_rx_params_valid = FALSE;

	lm_context->rx_param_dirty = 1;
	lm_context->tx_param_dirty = 1;

	lm_context->gpio_get = params->gpio_get;
	lm_context->gpio_present = params->gpio_present;

	lm_context->max_speed = params->max_speed;
	lm_context->sfp_detect_force_mode = params->sfp_detect_force_mode;

	lm_context->lm_pause = params->lm_pause;

	lm_context->led_config = params->led_config;

	lm_context->retimer_configured = FALSE;

	lm_context->link_state = AL_ETH_LM_LINK_DOWN;

	return (0);
}