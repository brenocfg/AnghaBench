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
typedef  int uint32_t ;
struct ath_softc {int /*<<< orphan*/  sc_ah; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATH_DEBUG_BTCOEX ; 
 int /*<<< orphan*/  DPRINTF (struct ath_softc*,int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  HAL_MCI_STATE_SEND_WLAN_CHANNELS ; 
 int /*<<< orphan*/  HAL_MCI_STATE_SEND_WLAN_COEX_VERSION ; 
 int /*<<< orphan*/  HAL_MCI_STATE_SET_BT_COEX_VERSION ; 
#define  MCI_GPM_COEX_BT_PROFILE_INFO 132 
#define  MCI_GPM_COEX_BT_STATUS_UPDATE 131 
 int /*<<< orphan*/  MCI_GPM_COEX_B_MAJOR_VERSION ; 
 int /*<<< orphan*/  MCI_GPM_COEX_B_MINOR_VERSION ; 
 int /*<<< orphan*/  MCI_GPM_COEX_B_WLAN_BITMAP ; 
#define  MCI_GPM_COEX_STATUS_QUERY 130 
#define  MCI_GPM_COEX_VERSION_QUERY 129 
#define  MCI_GPM_COEX_VERSION_RESPONSE 128 
 int ath_hal_btcoex_mci_state (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static void
ath_btcoex_mci_coex_msg(struct ath_softc *sc, uint8_t opcode,
    uint8_t *rx_payload)
{
	uint32_t version;
	uint8_t major;
	uint8_t minor;
	uint32_t seq_num;

	switch (opcode) {
	case MCI_GPM_COEX_VERSION_QUERY:
		DPRINTF(sc, ATH_DEBUG_BTCOEX,
		    "(MCI) Recv GPM COEX Version Query.\n");
		version = ath_hal_btcoex_mci_state(sc->sc_ah,
		    HAL_MCI_STATE_SEND_WLAN_COEX_VERSION, NULL);
		break;

	case MCI_GPM_COEX_VERSION_RESPONSE:
		DPRINTF(sc, ATH_DEBUG_BTCOEX,
		    "(MCI) Recv GPM COEX Version Response.\n");
		major = *(rx_payload + MCI_GPM_COEX_B_MAJOR_VERSION);
		minor = *(rx_payload + MCI_GPM_COEX_B_MINOR_VERSION);
		DPRINTF(sc, ATH_DEBUG_BTCOEX,
		    "(MCI) BT Coex version: %d.%d\n", major, minor);
		version = (major << 8) + minor;
		version = ath_hal_btcoex_mci_state(sc->sc_ah,
		    HAL_MCI_STATE_SET_BT_COEX_VERSION, &version);
		break;

	case MCI_GPM_COEX_STATUS_QUERY:
		DPRINTF(sc, ATH_DEBUG_BTCOEX,
		    "(MCI) Recv GPM COEX Status Query = 0x%02x.\n",
		    *(rx_payload + MCI_GPM_COEX_B_WLAN_BITMAP));
		ath_hal_btcoex_mci_state(sc->sc_ah,
		    HAL_MCI_STATE_SEND_WLAN_CHANNELS, NULL);
		break;

	case MCI_GPM_COEX_BT_PROFILE_INFO:
		/*
		 * XXX TODO: here is where we'd parse active profile
		 * info and make driver/stack choices as appropriate.
		 */
		DPRINTF(sc, ATH_DEBUG_BTCOEX,
		    "(MCI) TODO: Recv GPM COEX BT_Profile_Info.\n");
		break;

	case MCI_GPM_COEX_BT_STATUS_UPDATE:
		seq_num = *((uint32_t *)(rx_payload + 12));
		DPRINTF(sc, ATH_DEBUG_BTCOEX,
		    "(MCI) Recv GPM COEX BT_Status_Update: SEQ=%d\n",
		    seq_num);
		break;

	default:
		DPRINTF(sc, ATH_DEBUG_BTCOEX,
		    "(MCI) Unknown GPM COEX message = 0x%02x\n", opcode);
		break;
	}
}