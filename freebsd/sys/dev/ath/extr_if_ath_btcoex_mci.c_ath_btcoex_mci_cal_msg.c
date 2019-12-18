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
typedef  int /*<<< orphan*/  uint32_t ;
struct ath_softc {int /*<<< orphan*/  sc_ah; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATH_DEBUG_BTCOEX ; 
 int /*<<< orphan*/  DPRINTF (struct ath_softc*,int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  HAL_MCI_STATE_BT ; 
 int /*<<< orphan*/  HAL_MCI_STATE_SET_BT_CAL_START ; 
 int /*<<< orphan*/  MCI_BT_AWAKE ; 
 int /*<<< orphan*/  MCI_BT_CAL ; 
#define  MCI_GPM_BT_CAL_DONE 130 
#define  MCI_GPM_BT_CAL_GRANT 129 
#define  MCI_GPM_BT_CAL_REQ 128 
 int /*<<< orphan*/  MCI_GPM_SET_CAL_TYPE (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MCI_GPM_WLAN_CAL_DONE ; 
 int /*<<< orphan*/  ath_btcoex_mci_bt_cal_do (struct ath_softc*,int,int) ; 
 int /*<<< orphan*/  ath_btcoex_mci_send_gpm (struct ath_softc*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ath_hal_btcoex_mci_state (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
ath_btcoex_mci_cal_msg(struct ath_softc *sc, uint8_t opcode,
    uint8_t *rx_payload)
{
	uint32_t payload[4] = {0, 0, 0, 0};

	switch (opcode) {
	case MCI_GPM_BT_CAL_REQ:
		DPRINTF(sc, ATH_DEBUG_BTCOEX, "(MCI) receive BT_CAL_REQ\n");
		if (ath_hal_btcoex_mci_state(sc->sc_ah, HAL_MCI_STATE_BT,
		    NULL) == MCI_BT_AWAKE) {
			ath_hal_btcoex_mci_state(sc->sc_ah,
			    HAL_MCI_STATE_SET_BT_CAL_START, NULL);
			ath_btcoex_mci_bt_cal_do(sc, 1000, 1000);
		} else {
			DPRINTF(sc, ATH_DEBUG_BTCOEX,
			    "(MCI) State mismatches: %d\n",
			    ath_hal_btcoex_mci_state(sc->sc_ah,
			    HAL_MCI_STATE_BT, NULL));
		}
		break;
	case MCI_GPM_BT_CAL_DONE:
		DPRINTF(sc, ATH_DEBUG_BTCOEX, "(MCI) receive BT_CAL_DONE\n");
		if (ath_hal_btcoex_mci_state(sc->sc_ah, HAL_MCI_STATE_BT,
		    NULL) == MCI_BT_CAL) {
			DPRINTF(sc, ATH_DEBUG_BTCOEX,
			    "(MCI) ERROR ILLEGAL!\n");
		} else {
			DPRINTF(sc, ATH_DEBUG_BTCOEX,
			    "(MCI) BT not in CAL state.\n");
		}
		break;
	case MCI_GPM_BT_CAL_GRANT:
		DPRINTF(sc, ATH_DEBUG_BTCOEX, "(MCI) receive BT_CAL_GRANT\n");
		/* Send WLAN_CAL_DONE for now */
		DPRINTF(sc, ATH_DEBUG_BTCOEX, "(MCI) Send WLAN_CAL_DONE\n");
		MCI_GPM_SET_CAL_TYPE(payload, MCI_GPM_WLAN_CAL_DONE);
		ath_btcoex_mci_send_gpm(sc, &payload[0]);
		break;
	default:
		DPRINTF(sc, ATH_DEBUG_BTCOEX,
		    "(MCI) Unknown GPM CAL message.\n");
		break;
	}
}