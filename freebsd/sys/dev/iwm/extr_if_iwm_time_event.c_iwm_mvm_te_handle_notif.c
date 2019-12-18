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
struct iwm_time_event_notif {int unique_id; int action; int status; } ;
struct iwm_softc {int sc_time_event_end_ticks; int /*<<< orphan*/  sc_dev; int /*<<< orphan*/  sc_time_event_duration; } ;

/* Variables and functions */
 int /*<<< orphan*/  IWM_DEBUG_TE ; 
 int /*<<< orphan*/  IWM_DPRINTF (struct iwm_softc*,int /*<<< orphan*/ ,char*,...) ; 
 int IWM_TE_V2_NOTIF_HOST_EVENT_END ; 
 int IWM_TE_V2_NOTIF_HOST_EVENT_START ; 
 int TU_TO_HZ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int htole32 (int) ; 
 int /*<<< orphan*/  iwm_mvm_te_clear_data (struct iwm_softc*) ; 
 int le32toh (int) ; 
 int ticks ; 

__attribute__((used)) static void
iwm_mvm_te_handle_notif(struct iwm_softc *sc,
    struct iwm_time_event_notif *notif)
{
	IWM_DPRINTF(sc, IWM_DEBUG_TE,
	    "Handle time event notif - UID = 0x%x action %d\n",
	    le32toh(notif->unique_id),
	    le32toh(notif->action));

	if (!le32toh(notif->status)) {
		const char *msg;

		if (notif->action & htole32(IWM_TE_V2_NOTIF_HOST_EVENT_START))
			msg = "Time Event start notification failure";
		else
			msg = "Time Event end notification failure";

		IWM_DPRINTF(sc, IWM_DEBUG_TE, "%s\n", msg);
	}

	if (le32toh(notif->action) & IWM_TE_V2_NOTIF_HOST_EVENT_END) {
		IWM_DPRINTF(sc, IWM_DEBUG_TE,
		    "TE ended - current time %d, estimated end %d\n",
		    ticks, sc->sc_time_event_end_ticks);

		iwm_mvm_te_clear_data(sc);
	} else if (le32toh(notif->action) & IWM_TE_V2_NOTIF_HOST_EVENT_START) {
		sc->sc_time_event_end_ticks =
		    ticks + TU_TO_HZ(sc->sc_time_event_duration);
	} else {
		device_printf(sc->sc_dev, "Got TE with unknown action\n");
	}
}