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
struct iwm_umac_scan_complete {scalar_t__ ebs_status; int /*<<< orphan*/  status; int /*<<< orphan*/  uid; } ;
struct iwm_softc {int /*<<< orphan*/  last_ebs_successful; } ;
struct iwm_rx_packet {scalar_t__ data; } ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  IWM_DEBUG_SCAN ; 
 int /*<<< orphan*/  IWM_DPRINTF (struct iwm_softc*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ IWM_SCAN_EBS_INACTIVE ; 
 scalar_t__ IWM_SCAN_EBS_SUCCESS ; 
 int /*<<< orphan*/  iwm_mvm_ebs_status_str (scalar_t__) ; 
 int /*<<< orphan*/  iwm_mvm_offload_status_str (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  le32toh (int /*<<< orphan*/ ) ; 

void
iwm_mvm_rx_umac_scan_complete_notif(struct iwm_softc *sc,
    struct iwm_rx_packet *pkt)
{
	struct iwm_umac_scan_complete *notif = (void *)pkt->data;

	IWM_DPRINTF(sc, IWM_DEBUG_SCAN,
	    "Scan completed, uid %u, status %s, EBS status %s\n",
	    le32toh(notif->uid),
	    iwm_mvm_offload_status_str(notif->status),
	    iwm_mvm_ebs_status_str(notif->ebs_status));

	if (notif->ebs_status != IWM_SCAN_EBS_SUCCESS &&
	    notif->ebs_status != IWM_SCAN_EBS_INACTIVE)
		sc->last_ebs_successful = FALSE;
}