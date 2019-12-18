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
struct iwm_softc {int /*<<< orphan*/  sc_dev; } ;
struct iwm_mvm_rm_sta_cmd {int /*<<< orphan*/  sta_id; } ;
typedef  int /*<<< orphan*/  rm_sta_cmd ;

/* Variables and functions */
 int /*<<< orphan*/  IWM_REMOVE_STA ; 
 int /*<<< orphan*/  IWM_STATION_ID ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int iwm_mvm_send_cmd_pdu (struct iwm_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,struct iwm_mvm_rm_sta_cmd*) ; 

__attribute__((used)) static int
iwm_mvm_rm_sta_common(struct iwm_softc *sc)
{
	struct iwm_mvm_rm_sta_cmd rm_sta_cmd = {
		.sta_id = IWM_STATION_ID,
	};
	int ret;

	ret = iwm_mvm_send_cmd_pdu(sc, IWM_REMOVE_STA, 0,
				   sizeof(rm_sta_cmd), &rm_sta_cmd);
	if (ret) {
		device_printf(sc->sc_dev,
		    "Failed to remove station. Id=%d\n", IWM_STATION_ID);
		return ret;
	}

	return 0;
}