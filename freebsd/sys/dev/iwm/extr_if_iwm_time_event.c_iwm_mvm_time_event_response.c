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
struct iwm_time_event_resp {int /*<<< orphan*/  unique_id; int /*<<< orphan*/  id; } ;
struct iwm_softc {scalar_t__ sc_time_event_uid; } ;
struct TYPE_2__ {scalar_t__ code; } ;
struct iwm_rx_packet {scalar_t__ data; TYPE_1__ hdr; } ;

/* Variables and functions */
 int /*<<< orphan*/  IWM_DEBUG_TE ; 
 int /*<<< orphan*/  IWM_DPRINTF (struct iwm_softc*,int /*<<< orphan*/ ,char*,...) ; 
 scalar_t__ IWM_TE_BSS_STA_AGGRESSIVE_ASSOC ; 
 scalar_t__ IWM_TIME_EVENT_CMD ; 
 int iwm_rx_packet_payload_len (struct iwm_rx_packet*) ; 
 scalar_t__ le32toh (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
iwm_mvm_time_event_response(struct iwm_softc *sc, struct iwm_rx_packet *pkt,
    void *data)
{
	struct iwm_time_event_resp *resp;
	int resp_len = iwm_rx_packet_payload_len(pkt);

	if (pkt->hdr.code != IWM_TIME_EVENT_CMD ||
	    resp_len != sizeof(*resp)) {
		IWM_DPRINTF(sc, IWM_DEBUG_TE,
		    "Invalid TIME_EVENT_CMD response\n");
		return 1;
	}

	resp = (void *)pkt->data;

	/* we should never get a response to another TIME_EVENT_CMD here */
	if (le32toh(resp->id) != IWM_TE_BSS_STA_AGGRESSIVE_ASSOC) {
		IWM_DPRINTF(sc, IWM_DEBUG_TE,
		    "Got TIME_EVENT_CMD response with wrong id: %d\n",
		    le32toh(resp->id));
		return 0;
	}

	sc->sc_time_event_uid = le32toh(resp->unique_id);
	IWM_DPRINTF(sc, IWM_DEBUG_TE,
	    "TIME_EVENT_CMD response - UID = 0x%x\n", sc->sc_time_event_uid);
	return 1;
}