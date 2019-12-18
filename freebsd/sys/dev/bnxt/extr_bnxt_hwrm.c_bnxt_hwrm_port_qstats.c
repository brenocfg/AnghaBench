#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct hwrm_port_qstats_input {void* tx_stat_host_addr; void* rx_stat_host_addr; int /*<<< orphan*/  port_id; int /*<<< orphan*/  member_0; } ;
struct TYPE_4__ {int /*<<< orphan*/  idi_paddr; } ;
struct TYPE_6__ {int /*<<< orphan*/  idi_paddr; } ;
struct TYPE_5__ {int /*<<< orphan*/  port_id; } ;
struct bnxt_softc {TYPE_1__ hw_tx_port_stats; TYPE_3__ hw_rx_port_stats; TYPE_2__ pf; } ;
typedef  int /*<<< orphan*/  req ;

/* Variables and functions */
 int /*<<< orphan*/  BNXT_HWRM_LOCK (struct bnxt_softc*) ; 
 int /*<<< orphan*/  BNXT_HWRM_UNLOCK (struct bnxt_softc*) ; 
 int /*<<< orphan*/  HWRM_PORT_QSTATS ; 
 int _hwrm_send_message (struct bnxt_softc*,struct hwrm_port_qstats_input*,int) ; 
 int /*<<< orphan*/  bnxt_hwrm_cmd_hdr_init (struct bnxt_softc*,struct hwrm_port_qstats_input*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  htole16 (int /*<<< orphan*/ ) ; 
 void* htole64 (int /*<<< orphan*/ ) ; 

int
bnxt_hwrm_port_qstats(struct bnxt_softc *softc)
{
	struct hwrm_port_qstats_input req = {0};
	int rc = 0;

	bnxt_hwrm_cmd_hdr_init(softc, &req, HWRM_PORT_QSTATS);

	req.port_id = htole16(softc->pf.port_id);
	req.rx_stat_host_addr = htole64(softc->hw_rx_port_stats.idi_paddr);
	req.tx_stat_host_addr = htole64(softc->hw_tx_port_stats.idi_paddr);

	BNXT_HWRM_LOCK(softc);
	rc = _hwrm_send_message(softc, &req, sizeof(req));
	BNXT_HWRM_UNLOCK(softc);

	return rc;
}