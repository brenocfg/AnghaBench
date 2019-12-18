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
struct iwm_vap {int dummy; } ;
struct iwm_softc {int dummy; } ;
struct iwm_beacon_filter_cmd {int /*<<< orphan*/  bf_enable_beacon_filter; int /*<<< orphan*/  member_0; } ;

/* Variables and functions */
 int /*<<< orphan*/  IWM_BF_CMD_CONFIG_DEFAULTS ; 
 int _iwm_mvm_enable_beacon_filter (struct iwm_softc*,struct iwm_vap*,struct iwm_beacon_filter_cmd*) ; 
 int /*<<< orphan*/  htole32 (int) ; 

int
iwm_mvm_enable_beacon_filter(struct iwm_softc *sc, struct iwm_vap *ivp)
{
	struct iwm_beacon_filter_cmd cmd = {
		IWM_BF_CMD_CONFIG_DEFAULTS,
		.bf_enable_beacon_filter = htole32(1),
	};

	return _iwm_mvm_enable_beacon_filter(sc, ivp, &cmd);
}