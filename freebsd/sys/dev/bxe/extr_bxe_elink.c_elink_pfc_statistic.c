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
typedef  int /*<<< orphan*/  uint32_t ;
struct elink_vars {scalar_t__ mac_type; int /*<<< orphan*/  link_up; } ;
struct elink_params {struct bxe_softc* sc; } ;
struct bxe_softc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ELINK_DEBUG_P0 (struct bxe_softc*,char*) ; 
 scalar_t__ ELINK_MAC_TYPE_EMAC ; 
 int /*<<< orphan*/  elink_emac_get_pfc_stat (struct elink_params*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

void elink_pfc_statistic(struct elink_params *params, struct elink_vars *vars,
			 uint32_t pfc_frames_sent[2],
			 uint32_t pfc_frames_received[2])
{
	/* Read pfc statistic */
	struct bxe_softc *sc = params->sc;

	ELINK_DEBUG_P0(sc, "pfc statistic\n");

	if (!vars->link_up)
		return;

	if (vars->mac_type == ELINK_MAC_TYPE_EMAC) {
		ELINK_DEBUG_P0(sc, "About to read PFC stats from EMAC\n");
		elink_emac_get_pfc_stat(params, pfc_frames_sent,
					pfc_frames_received);
	}
}