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
typedef  int uint8_t ;
typedef  scalar_t__ uint32_t ;
struct elink_params {int port; struct bxe_softc* sc; } ;
struct bxe_softc {int dummy; } ;

/* Variables and functions */
 int ELINK_DCBX_E3B0_MAX_NUM_COS_PORT0 ; 
 int ELINK_DCBX_E3B0_MAX_NUM_COS_PORT1 ; 
 scalar_t__ PBF_REG_COS0_UPPER_BOUND_P0 ; 
 scalar_t__ PBF_REG_COS0_UPPER_BOUND_P1 ; 
 int /*<<< orphan*/  REG_WR (struct bxe_softc*,scalar_t__,scalar_t__ const) ; 
 scalar_t__ elink_ets_get_credit_upper_bound (scalar_t__ const) ; 

__attribute__((used)) static void elink_ets_e3b0_set_credit_upper_bound_pbf(
	const struct elink_params *params,
	const uint32_t min_w_val)
{
	struct bxe_softc *sc = params->sc;
	const uint32_t credit_upper_bound =
	    elink_ets_get_credit_upper_bound(min_w_val);
	const uint8_t port = params->port;
	uint32_t base_upper_bound = 0;
	uint8_t max_cos = 0;
	uint8_t i = 0;
	/* In 2 port mode port0 has COS0-5 that can be used for WFQ.In 4
	 * port mode port1 has COS0-2 that can be used for WFQ.
	 */
	if (!port) {
		base_upper_bound = PBF_REG_COS0_UPPER_BOUND_P0;
		max_cos = ELINK_DCBX_E3B0_MAX_NUM_COS_PORT0;
	} else {
		base_upper_bound = PBF_REG_COS0_UPPER_BOUND_P1;
		max_cos = ELINK_DCBX_E3B0_MAX_NUM_COS_PORT1;
	}

	for (i = 0; i < max_cos; i++)
		REG_WR(sc, base_upper_bound + (i << 2), credit_upper_bound);
}