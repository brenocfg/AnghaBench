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
typedef  int /*<<< orphan*/  uint16_t ;
struct iwm_softc {int /*<<< orphan*/  sc_notif_wait; } ;
struct iwm_notification_wait {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  IWM_DEBUG_SCAN ; 
 int /*<<< orphan*/  IWM_DPRINTF (struct iwm_softc*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  IWM_LOCK (struct iwm_softc*) ; 
#define  IWM_SCAN_COMPLETE_UMAC 129 
#define  IWM_SCAN_OFFLOAD_COMPLETE 128 
 int /*<<< orphan*/  IWM_UCODE_TLV_CAPA_UMAC_SCAN ; 
 int /*<<< orphan*/  IWM_UNLOCK (struct iwm_softc*) ; 
 int /*<<< orphan*/  hz ; 
 scalar_t__ iwm_fw_has_capa (struct iwm_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iwm_init_notification_wait (int /*<<< orphan*/ ,struct iwm_notification_wait*,int /*<<< orphan*/  const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int iwm_mvm_lmac_scan_abort (struct iwm_softc*) ; 
 int iwm_mvm_umac_scan_abort (struct iwm_softc*) ; 
 int /*<<< orphan*/  iwm_remove_notification (int /*<<< orphan*/ ,struct iwm_notification_wait*) ; 
 int iwm_wait_notification (int /*<<< orphan*/ ,struct iwm_notification_wait*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nitems (int /*<<< orphan*/  const*) ; 

int
iwm_mvm_scan_stop_wait(struct iwm_softc *sc)
{
	struct iwm_notification_wait wait_scan_done;
	static const uint16_t scan_done_notif[] = { IWM_SCAN_COMPLETE_UMAC,
						   IWM_SCAN_OFFLOAD_COMPLETE, };
	int ret;

	iwm_init_notification_wait(sc->sc_notif_wait, &wait_scan_done,
				   scan_done_notif, nitems(scan_done_notif),
				   NULL, NULL);

	IWM_DPRINTF(sc, IWM_DEBUG_SCAN, "Preparing to stop scan\n");

	if (iwm_fw_has_capa(sc, IWM_UCODE_TLV_CAPA_UMAC_SCAN))
		ret = iwm_mvm_umac_scan_abort(sc);
	else
		ret = iwm_mvm_lmac_scan_abort(sc);

	if (ret) {
		IWM_DPRINTF(sc, IWM_DEBUG_SCAN, "couldn't stop scan\n");
		iwm_remove_notification(sc->sc_notif_wait, &wait_scan_done);
		return ret;
	}

	IWM_UNLOCK(sc);
	ret = iwm_wait_notification(sc->sc_notif_wait, &wait_scan_done, hz);
	IWM_LOCK(sc);

	return ret;
}