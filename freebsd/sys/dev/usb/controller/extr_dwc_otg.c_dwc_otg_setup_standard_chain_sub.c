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
struct dwc_otg_td {int /*<<< orphan*/  tt_xactpos; scalar_t__ tt_scheduled; scalar_t__ errcnt; scalar_t__ state; void** channel; scalar_t__ did_nak; scalar_t__ got_short; scalar_t__ set_toggle; int /*<<< orphan*/  alt_next; int /*<<< orphan*/  short_pkt; int /*<<< orphan*/  did_stall; scalar_t__ npkt; scalar_t__ error_stall; scalar_t__ error_any; scalar_t__ tx_bytes; int /*<<< orphan*/  remainder; int /*<<< orphan*/  offset; int /*<<< orphan*/  pc; int /*<<< orphan*/  func; struct dwc_otg_td* obj_next; } ;
struct dwc_otg_std_temp {int /*<<< orphan*/  setup_alt_next; int /*<<< orphan*/  short_pkt; int /*<<< orphan*/  did_stall; int /*<<< orphan*/  len; int /*<<< orphan*/  offset; int /*<<< orphan*/  pc; int /*<<< orphan*/  func; struct dwc_otg_td* td_next; struct dwc_otg_td* td; } ;

/* Variables and functions */
 void* DWC_OTG_MAX_CHANNELS ; 
 int /*<<< orphan*/  HCSPLT_XACTPOS_BEGIN ; 

__attribute__((used)) static void
dwc_otg_setup_standard_chain_sub(struct dwc_otg_std_temp *temp)
{
	struct dwc_otg_td *td;

	/* get current Transfer Descriptor */
	td = temp->td_next;
	temp->td = td;

	/* prepare for next TD */
	temp->td_next = td->obj_next;

	/* fill out the Transfer Descriptor */
	td->func = temp->func;
	td->pc = temp->pc;
	td->offset = temp->offset;
	td->remainder = temp->len;
	td->tx_bytes = 0;
	td->error_any = 0;
	td->error_stall = 0;
	td->npkt = 0;
	td->did_stall = temp->did_stall;
	td->short_pkt = temp->short_pkt;
	td->alt_next = temp->setup_alt_next;
	td->set_toggle = 0;
	td->got_short = 0;
	td->did_nak = 0;
	td->channel[0] = DWC_OTG_MAX_CHANNELS;
	td->channel[1] = DWC_OTG_MAX_CHANNELS;
	td->channel[2] = DWC_OTG_MAX_CHANNELS;
	td->state = 0;
	td->errcnt = 0;
	td->tt_scheduled = 0;
	td->tt_xactpos = HCSPLT_XACTPOS_BEGIN;
}