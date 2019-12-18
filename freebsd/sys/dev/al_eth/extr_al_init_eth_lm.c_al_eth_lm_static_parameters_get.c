#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct al_serdes_adv_tx_params {int dummy; } ;
struct al_serdes_adv_rx_params {int dummy; } ;
struct al_eth_lm_context {int /*<<< orphan*/  lane; TYPE_1__* serdes_obj; struct al_serdes_adv_rx_params rx_params_override; scalar_t__ serdes_rx_params_valid; struct al_serdes_adv_tx_params tx_params_override; scalar_t__ serdes_tx_params_valid; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* rx_advanced_params_get ) (TYPE_1__*,int /*<<< orphan*/ ,struct al_serdes_adv_rx_params*) ;int /*<<< orphan*/  (* tx_advanced_params_get ) (TYPE_1__*,int /*<<< orphan*/ ,struct al_serdes_adv_tx_params*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (TYPE_1__*,int /*<<< orphan*/ ,struct al_serdes_adv_tx_params*) ; 
 int /*<<< orphan*/  stub2 (TYPE_1__*,int /*<<< orphan*/ ,struct al_serdes_adv_rx_params*) ; 

int
al_eth_lm_static_parameters_get(struct al_eth_lm_context *lm_context,
    struct al_serdes_adv_tx_params *tx_params,
    struct al_serdes_adv_rx_params *rx_params)
{

	if (tx_params != NULL) {
		if (lm_context->serdes_tx_params_valid)
			*tx_params = lm_context->tx_params_override;
		else
			lm_context->serdes_obj->tx_advanced_params_get(
							lm_context->serdes_obj,
							lm_context->lane,
							tx_params);
	}

	if (rx_params != NULL) {
		if (lm_context->serdes_rx_params_valid)
			*rx_params = lm_context->rx_params_override;
		else
			lm_context->serdes_obj->rx_advanced_params_get(
							lm_context->serdes_obj,
							lm_context->lane,
							rx_params);
	}

	return (0);
}