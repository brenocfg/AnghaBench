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
struct iwm_time_event_notif {int /*<<< orphan*/  action; int /*<<< orphan*/  unique_id; } ;
struct iwm_softc {int dummy; } ;
struct iwm_rx_packet {scalar_t__ data; } ;

/* Variables and functions */
 int /*<<< orphan*/  IWM_DEBUG_TE ; 
 int /*<<< orphan*/  IWM_DPRINTF (struct iwm_softc*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iwm_mvm_te_handle_notif (struct iwm_softc*,struct iwm_time_event_notif*) ; 
 int /*<<< orphan*/  le32toh (int /*<<< orphan*/ ) ; 

void
iwm_mvm_rx_time_event_notif(struct iwm_softc *sc, struct iwm_rx_packet *pkt)
{
	struct iwm_time_event_notif *notif = (void *)pkt->data;

	IWM_DPRINTF(sc, IWM_DEBUG_TE,
	    "Time event notification - UID = 0x%x action %d\n",
	    le32toh(notif->unique_id),
	    le32toh(notif->action));

	iwm_mvm_te_handle_notif(sc, notif);
}