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
struct TYPE_2__ {scalar_t__ bf_enabled; } ;
struct iwm_softc {TYPE_1__ sc_bf; } ;
struct iwm_beacon_filter_cmd {int dummy; } ;

/* Variables and functions */
 int iwm_mvm_beacon_filter_send_cmd (struct iwm_softc*,struct iwm_beacon_filter_cmd*) ; 

int
iwm_mvm_disable_beacon_filter(struct iwm_softc *sc)
{
	struct iwm_beacon_filter_cmd cmd = {};
	int ret;

	ret = iwm_mvm_beacon_filter_send_cmd(sc, &cmd);
	if (ret == 0)
		sc->sc_bf.bf_enabled = 0;

	return ret;
}