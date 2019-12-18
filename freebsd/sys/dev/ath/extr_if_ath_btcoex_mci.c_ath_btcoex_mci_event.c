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
struct ath_softc {int /*<<< orphan*/  sc_ah; int /*<<< orphan*/  sc_btcoex_mci; } ;
typedef  scalar_t__ ATH_BT_COEX_EVENT ;

/* Variables and functions */
 scalar_t__ ATH_COEX_EVENT_BT_NOOP ; 
 int /*<<< orphan*/  ATH_DEBUG_BTCOEX ; 
 int /*<<< orphan*/  DPRINTF (struct ath_softc*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  HAL_MCI_STATE_ENABLE ; 
 int /*<<< orphan*/  HAL_MCI_STATE_NEED_FLUSH_BT_INFO ; 
 int /*<<< orphan*/  HAL_MCI_STATE_SEND_STATUS_QUERY ; 
 scalar_t__ ath_hal_btcoex_mci_state (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
ath_btcoex_mci_event(struct ath_softc *sc, ATH_BT_COEX_EVENT nevent,
    void *param)
{

	if (! sc->sc_btcoex_mci)
		return;

	/*
	 * Check whether we need to flush our local profile cache.
	 * If we do, then at (XXX TODO) we should flush our state,
	 * then wait for the MCI response with the updated profile list.
	 */
	if (ath_hal_btcoex_mci_state(sc->sc_ah,
	    HAL_MCI_STATE_NEED_FLUSH_BT_INFO, NULL) != 0) {
		uint32_t data = 0;

		if (ath_hal_btcoex_mci_state(sc->sc_ah,
		    HAL_MCI_STATE_ENABLE, NULL) != 0) {
			DPRINTF(sc, ATH_DEBUG_BTCOEX,
			    "(MCI) Flush BT profile\n");
			/*
			 * XXX TODO: flush profile state on the ath(4)
			 * driver side; subsequent messages will come
			 * through with the current list of active
			 * profiles.
			 */
			ath_hal_btcoex_mci_state(sc->sc_ah,
			    HAL_MCI_STATE_NEED_FLUSH_BT_INFO, &data);
			ath_hal_btcoex_mci_state(sc->sc_ah,
			    HAL_MCI_STATE_SEND_STATUS_QUERY, NULL);
		}
	}
	if (nevent == ATH_COEX_EVENT_BT_NOOP) {
		DPRINTF(sc, ATH_DEBUG_BTCOEX, "(MCI) BT_NOOP\n");
		return;
	}
}