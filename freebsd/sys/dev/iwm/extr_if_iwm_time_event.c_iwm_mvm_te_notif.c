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
struct iwm_time_event_notif {int /*<<< orphan*/  status; int /*<<< orphan*/  unique_id; } ;
struct iwm_softc {scalar_t__ sc_time_event_uid; } ;
struct TYPE_2__ {scalar_t__ code; } ;
struct iwm_rx_packet {scalar_t__ data; TYPE_1__ hdr; } ;

/* Variables and functions */
 int /*<<< orphan*/  IWM_DEBUG_TE ; 
 int /*<<< orphan*/  IWM_DPRINTF (struct iwm_softc*,int /*<<< orphan*/ ,char*,...) ; 
 scalar_t__ IWM_TIME_EVENT_NOTIFICATION ; 
 int iwm_rx_packet_payload_len (struct iwm_rx_packet*) ; 
 scalar_t__ le32toh (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
iwm_mvm_te_notif(struct iwm_softc *sc, struct iwm_rx_packet *pkt,
    void *data)
{
	struct iwm_time_event_notif *resp;
	int resp_len = iwm_rx_packet_payload_len(pkt);

	if (pkt->hdr.code != IWM_TIME_EVENT_NOTIFICATION ||
	    resp_len != sizeof(*resp)) {
		IWM_DPRINTF(sc, IWM_DEBUG_TE,
		    "Invalid TIME_EVENT_NOTIFICATION response\n");
		return 1;
	}

	resp = (void *)pkt->data;

	/* te_data->uid is already set in the TIME_EVENT_CMD response */
	if (le32toh(resp->unique_id) != sc->sc_time_event_uid)
		return false;

	IWM_DPRINTF(sc, IWM_DEBUG_TE,
	    "TIME_EVENT_NOTIFICATION response - UID = 0x%x\n",
	    sc->sc_time_event_uid);
	if (!resp->status) {
		IWM_DPRINTF(sc, IWM_DEBUG_TE,
		    "TIME_EVENT_NOTIFICATION received but not executed\n");
	}

	return 1;
}