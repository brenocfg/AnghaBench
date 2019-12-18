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
struct si_sm_data {int error_retries; int BT_CAP_retries; unsigned char seq; int /*<<< orphan*/  state; TYPE_1__* io; int /*<<< orphan*/  nonzero_status; int /*<<< orphan*/  BT_CAP_req2rsp; int /*<<< orphan*/  timeout; } ;
typedef  enum si_sm_result { ____Placeholder_si_sm_result } si_sm_result ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 unsigned char BT_B_BUSY ; 
 int /*<<< orphan*/  BT_STATE_IDLE ; 
 int /*<<< orphan*/  BT_STATE_LONG_BUSY ; 
 int /*<<< orphan*/  BT_STATE_RESET1 ; 
 int /*<<< orphan*/  BT_STATE_RESTART ; 
 unsigned char IPMI_NODE_BUSY_ERR ; 
#define  IPMI_TIMEOUT_ERR 128 
 int SI_SM_CALL_WITHOUT_DELAY ; 
 int SI_SM_TRANSACTION_COMPLETE ; 
 int /*<<< orphan*/  STATE2TXT ; 
 int /*<<< orphan*/  STATUS2TXT ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  force_result (struct si_sm_data*,unsigned char) ; 
 int /*<<< orphan*/  pr_cont (char*,int) ; 

__attribute__((used)) static enum si_sm_result error_recovery(struct si_sm_data *bt,
					unsigned char status,
					unsigned char cCode)
{
	char *reason;

	bt->timeout = bt->BT_CAP_req2rsp;

	switch (cCode) {
	case IPMI_TIMEOUT_ERR:
		reason = "timeout";
		break;
	default:
		reason = "internal error";
		break;
	}

	dev_warn(bt->io->dev, "IPMI BT: %s in %s %s ", /* open-ended line */
		 reason, STATE2TXT, STATUS2TXT);

	/*
	 * Per the IPMI spec, retries are based on the sequence number
	 * known only to this module, so manage a restart here.
	 */
	(bt->error_retries)++;
	if (bt->error_retries < bt->BT_CAP_retries) {
		pr_cont("%d retries left\n",
			bt->BT_CAP_retries - bt->error_retries);
		bt->state = BT_STATE_RESTART;
		return SI_SM_CALL_WITHOUT_DELAY;
	}

	dev_warn(bt->io->dev, "failed %d retries, sending error response\n",
		 bt->BT_CAP_retries);
	if (!bt->nonzero_status)
		dev_err(bt->io->dev, "stuck, try power cycle\n");

	/* this is most likely during insmod */
	else if (bt->seq <= (unsigned char)(bt->BT_CAP_retries & 0xFF)) {
		dev_warn(bt->io->dev, "BT reset (takes 5 secs)\n");
		bt->state = BT_STATE_RESET1;
		return SI_SM_CALL_WITHOUT_DELAY;
	}

	/*
	 * Concoct a useful error message, set up the next state, and
	 * be done with this sequence.
	 */

	bt->state = BT_STATE_IDLE;
	switch (cCode) {
	case IPMI_TIMEOUT_ERR:
		if (status & BT_B_BUSY) {
			cCode = IPMI_NODE_BUSY_ERR;
			bt->state = BT_STATE_LONG_BUSY;
		}
		break;
	default:
		break;
	}
	force_result(bt, cCode);
	return SI_SM_TRANSACTION_COMPLETE;
}