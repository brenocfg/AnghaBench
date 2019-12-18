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
struct al_serdes_adv_tx_params {int dummy; } ;
struct al_serdes_adv_rx_params {int dummy; } ;
struct al_eth_lm_context {int tx_param_dirty; int rx_param_dirty; void* serdes_rx_params_valid; struct al_serdes_adv_rx_params rx_params_override; void* serdes_tx_params_valid; struct al_serdes_adv_tx_params tx_params_override; } ;

/* Variables and functions */
 void* TRUE ; 

int
al_eth_lm_static_parameters_override(struct al_eth_lm_context *lm_context,
    struct al_serdes_adv_tx_params *tx_params,
    struct al_serdes_adv_rx_params *rx_params)
{

	if (tx_params != NULL) {
		lm_context->tx_params_override = *tx_params;
		lm_context->tx_param_dirty = 1;
		lm_context->serdes_tx_params_valid = TRUE;
	}

	if (rx_params != NULL) {
		lm_context->rx_params_override = *rx_params;
		lm_context->rx_param_dirty = 1;
		lm_context->serdes_rx_params_valid = TRUE;
	}

	return (0);
}