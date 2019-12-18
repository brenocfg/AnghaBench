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
struct al_eth_lm_context {void* serdes_tx_params_valid; } ;
typedef  scalar_t__ boolean_t ;

/* Variables and functions */
 void* FALSE ; 

int
al_eth_lm_static_parameters_override_disable(struct al_eth_lm_context *lm_context,
    boolean_t tx_params, boolean_t rx_params)
{

	if (tx_params != 0)
		lm_context->serdes_tx_params_valid = FALSE;
	if (rx_params != 0)
		lm_context->serdes_tx_params_valid = FALSE;

	return (0);
}