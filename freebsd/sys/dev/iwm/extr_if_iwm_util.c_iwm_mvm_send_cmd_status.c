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
typedef  int /*<<< orphan*/  uint32_t ;
struct iwm_softc {int dummy; } ;
struct TYPE_2__ {int flags; } ;
struct iwm_rx_packet {scalar_t__ data; TYPE_1__ hdr; } ;
struct iwm_host_cmd {int flags; struct iwm_rx_packet* resp_pkt; } ;
struct iwm_cmd_response {int /*<<< orphan*/  status; } ;

/* Variables and functions */
 int EIO ; 
 int IWM_CMD_FAILED_MSK ; 
 int IWM_CMD_SYNC ; 
 int IWM_CMD_WANT_SKB ; 
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int /*<<< orphan*/  iwm_free_resp (struct iwm_softc*,struct iwm_host_cmd*) ; 
 int iwm_rx_packet_payload_len (struct iwm_rx_packet*) ; 
 int iwm_send_cmd (struct iwm_softc*,struct iwm_host_cmd*) ; 
 int /*<<< orphan*/  le32toh (int /*<<< orphan*/ ) ; 

int
iwm_mvm_send_cmd_status(struct iwm_softc *sc,
	struct iwm_host_cmd *cmd, uint32_t *status)
{
	struct iwm_rx_packet *pkt;
	struct iwm_cmd_response *resp;
	int error, resp_len;

	KASSERT((cmd->flags & IWM_CMD_WANT_SKB) == 0,
	    ("invalid command"));
	cmd->flags |= IWM_CMD_SYNC | IWM_CMD_WANT_SKB;

	if ((error = iwm_send_cmd(sc, cmd)) != 0)
		return error;
	pkt = cmd->resp_pkt;

	/* Can happen if RFKILL is asserted */
	if (!pkt) {
		error = 0;
		goto out_free_resp;
	}

	if (pkt->hdr.flags & IWM_CMD_FAILED_MSK) {
		error = EIO;
		goto out_free_resp;
	}

	resp_len = iwm_rx_packet_payload_len(pkt);
	if (resp_len != sizeof(*resp)) {
		error = EIO;
		goto out_free_resp;
	}

	resp = (void *)pkt->data;
	*status = le32toh(resp->status);
 out_free_resp:
	iwm_free_resp(sc, cmd);
	return error;
}