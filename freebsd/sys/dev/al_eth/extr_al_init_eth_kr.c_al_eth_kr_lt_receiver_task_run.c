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
struct al_eth_kr_data {int /*<<< orphan*/  adapter; } ;
struct al_eth_kr_coef_up_data {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  AL_ETH_AN__LT_LANE_0 ; 
 int /*<<< orphan*/  al_eth_coeff_req_handle (struct al_eth_kr_data*,struct al_eth_kr_coef_up_data*) ; 
 scalar_t__ al_eth_kr_receiver_frame_lock_get (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ al_eth_lp_coeff_up_change (struct al_eth_kr_data*,struct al_eth_kr_coef_up_data*) ; 
 int /*<<< orphan*/  al_eth_lp_coeff_up_get (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct al_eth_kr_coef_up_data*) ; 

__attribute__((used)) static int
al_eth_kr_lt_receiver_task_run(struct al_eth_kr_data *kr_data)
{
	struct al_eth_kr_coef_up_data new_lpcoeff;

	/*
	 * First inspect status of the link. It may have dropped frame lock as
	 * the remote did some reconfiguration of its serdes.
	 * Then we simply have nothing to do and return immediately as caller
	 * will call us continuously until lock comes back.
	 */

	if (al_eth_kr_receiver_frame_lock_get(kr_data->adapter,
	    AL_ETH_AN__LT_LANE_0) != 0) {
		return (0);
	}

	/* check if a new update command was received */
	al_eth_lp_coeff_up_get(kr_data->adapter,
	    AL_ETH_AN__LT_LANE_0, &new_lpcoeff);

	if (al_eth_lp_coeff_up_change(kr_data, &new_lpcoeff) != 0) {
		/* got some new coefficient update request. */
		al_eth_coeff_req_handle(kr_data, &new_lpcoeff);
	}

	return (0);
}