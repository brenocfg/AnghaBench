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
struct ecore_queue_setup_params {int /*<<< orphan*/  flags; } ;
struct TYPE_3__ {struct ecore_queue_setup_params setup; } ;
struct ecore_queue_state_params {TYPE_1__ params; } ;
struct TYPE_4__ {int tpa_en; } ;
struct client_init_ramrod_data {TYPE_2__ rx; } ;
struct bxe_softc {int dummy; } ;

/* Variables and functions */
 int CLIENT_INIT_RX_DATA_TPA_EN_IPV6 ; 
 int /*<<< orphan*/  ECORE_Q_FLG_TPA_IPV6 ; 
 int ECORE_TEST_BIT (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ecore_q_fill_setup_data_e2(struct bxe_softc *sc,
				struct ecore_queue_state_params *cmd_params,
				struct client_init_ramrod_data *data)
{
	struct ecore_queue_setup_params *params = &cmd_params->params.setup;

	/* Rx data */

	/* IPv6 TPA supported for E2 and above only */
	data->rx.tpa_en |= ECORE_TEST_BIT(ECORE_Q_FLG_TPA_IPV6,
					  &params->flags) *
				CLIENT_INIT_RX_DATA_TPA_EN_IPV6;
}