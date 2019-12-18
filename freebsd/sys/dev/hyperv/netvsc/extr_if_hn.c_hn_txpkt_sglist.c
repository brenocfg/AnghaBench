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
struct hn_txdesc {scalar_t__ chim_index; scalar_t__ chim_size; int /*<<< orphan*/  send_ctx; } ;
struct hn_tx_ring {int /*<<< orphan*/  hn_gpa_cnt; int /*<<< orphan*/  hn_gpa; int /*<<< orphan*/  hn_chan; } ;

/* Variables and functions */
 scalar_t__ HN_NVS_CHIM_IDX_INVALID ; 
 int /*<<< orphan*/  HN_NVS_RNDIS_MTYPE_DATA ; 
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int hn_nvs_send_rndis_sglist (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
hn_txpkt_sglist(struct hn_tx_ring *txr, struct hn_txdesc *txd)
{

	KASSERT(txd->chim_index == HN_NVS_CHIM_IDX_INVALID &&
	    txd->chim_size == 0, ("invalid rndis sglist txd"));
	return (hn_nvs_send_rndis_sglist(txr->hn_chan, HN_NVS_RNDIS_MTYPE_DATA,
	    &txd->send_ctx, txr->hn_gpa, txr->hn_gpa_cnt));
}