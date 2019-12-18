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
struct iwm_vap {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  ba_enabled; } ;
struct iwm_softc {TYPE_1__ sc_bf; } ;
struct iwm_beacon_filter_cmd {int /*<<< orphan*/  ba_enable_beacon_abort; } ;

/* Variables and functions */
 int /*<<< orphan*/  htole32 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
iwm_mvm_beacon_filter_set_cqm_params(struct iwm_softc *sc,
	struct iwm_vap *ivp, struct iwm_beacon_filter_cmd *cmd)
{
	cmd->ba_enable_beacon_abort = htole32(sc->sc_bf.ba_enabled);
}