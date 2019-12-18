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
struct iwm_softc {int /*<<< orphan*/  sc_dev; } ;
struct iwm_host_cmd {int /*<<< orphan*/  data; int /*<<< orphan*/  len; int /*<<< orphan*/  id; } ;

/* Variables and functions */
 int /*<<< orphan*/  IWM_REPLY_THERMAL_MNG_BACKOFF ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ iwm_send_cmd (struct iwm_softc*,struct iwm_host_cmd*) ; 

__attribute__((used)) static void
iwm_mvm_tt_tx_backoff(struct iwm_softc *sc, uint32_t backoff)
{
	struct iwm_host_cmd cmd = {
		.id = IWM_REPLY_THERMAL_MNG_BACKOFF,
		.len = { sizeof(uint32_t), },
		.data = { &backoff, },
	};

	if (iwm_send_cmd(sc, &cmd) != 0) {
		device_printf(sc->sc_dev,
		    "failed to change thermal tx backoff\n");
	}
}