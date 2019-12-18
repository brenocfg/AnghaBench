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
typedef  int uint32_t ;
struct al_eth_kr_data {int /*<<< orphan*/  lane; TYPE_1__* serdes_obj; } ;
typedef  enum al_serdes_tx_deemph_param { ____Placeholder_al_serdes_tx_deemph_param } al_serdes_tx_deemph_param ;
typedef  enum al_eth_kr_cl72_cstate { ____Placeholder_al_eth_kr_cl72_cstate } al_eth_kr_cl72_cstate ;
struct TYPE_3__ {int /*<<< orphan*/  (* tx_deemph_dec ) (TYPE_1__*,int /*<<< orphan*/ ,int) ;int /*<<< orphan*/  (* tx_deemph_inc ) (TYPE_1__*,int /*<<< orphan*/ ,int) ;} ;

/* Variables and functions */
#define  AL_PHY_KR_COEF_UP_DEC 130 
#define  AL_PHY_KR_COEF_UP_HOLD 129 
#define  AL_PHY_KR_COEF_UP_INC 128 
 int C72_CSTATE_MAX ; 
 int C72_CSTATE_MIN ; 
 int C72_CSTATE_NOT_UPDATED ; 
 int C72_CSTATE_UPDATED ; 
 int /*<<< orphan*/  stub1 (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub2 (TYPE_1__*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static enum al_eth_kr_cl72_cstate
al_eth_lt_coeff_set(struct al_eth_kr_data *kr_data,
    enum al_serdes_tx_deemph_param param, uint32_t op)
{
	enum al_eth_kr_cl72_cstate status = 0;

	switch (op) {
	case AL_PHY_KR_COEF_UP_HOLD:
		/* no need to update the serdes - return not updated*/
		status = C72_CSTATE_NOT_UPDATED;
		break;
	case AL_PHY_KR_COEF_UP_INC:
		status = C72_CSTATE_UPDATED;

		if (kr_data->serdes_obj->tx_deemph_inc(
					kr_data->serdes_obj,
					kr_data->lane,
					param) == 0)
			status = C72_CSTATE_MAX;
		break;
	case AL_PHY_KR_COEF_UP_DEC:
		status = C72_CSTATE_UPDATED;

		if (kr_data->serdes_obj->tx_deemph_dec(
					kr_data->serdes_obj,
					kr_data->lane,
					param) == 0)
			status = C72_CSTATE_MIN;
		break;
	default: /* 3=reserved */
		break;
	}

	return (status);
}