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
struct ath_tx_status {int ts_shortretry; int ts_longretry; } ;
struct ath_softc {int dummy; } ;
struct ath_rc_series {int dummy; } ;
struct ath_node {int /*<<< orphan*/  an_node; } ;
struct amrr_node {scalar_t__ amn_interval; scalar_t__ amn_ticks; int /*<<< orphan*/  amn_tx_failure_cnt; int /*<<< orphan*/  amn_tx_try3_cnt; int /*<<< orphan*/  amn_tx_try2_cnt; int /*<<< orphan*/  amn_tx_try1_cnt; int /*<<< orphan*/  amn_tx_try0_cnt; } ;

/* Variables and functions */
 struct amrr_node* ATH_NODE_AMRR (struct ath_node*) ; 
 int /*<<< orphan*/  ath_rate_ctl (struct ath_softc*,int /*<<< orphan*/ *) ; 
 scalar_t__ ticks ; 

void
ath_rate_tx_complete(struct ath_softc *sc, struct ath_node *an,
	const struct ath_rc_series *rc, const struct ath_tx_status *ts,
	int frame_size, int nframes, int nbad)
{
	struct amrr_node *amn = ATH_NODE_AMRR(an);
	int sr = ts->ts_shortretry;
	int lr = ts->ts_longretry;
	int retry_count = sr + lr;

	amn->amn_tx_try0_cnt++;
	if (retry_count == 1) {
		amn->amn_tx_try1_cnt++;
	} else if (retry_count == 2) {
		amn->amn_tx_try1_cnt++;
		amn->amn_tx_try2_cnt++;
	} else if (retry_count == 3) {
		amn->amn_tx_try1_cnt++;
		amn->amn_tx_try2_cnt++;
		amn->amn_tx_try3_cnt++;
	} else if (retry_count > 3) {
		amn->amn_tx_try1_cnt++;
		amn->amn_tx_try2_cnt++;
		amn->amn_tx_try3_cnt++;
		amn->amn_tx_failure_cnt++;
	}
	if (amn->amn_interval != 0 &&
	    ticks - amn->amn_ticks > amn->amn_interval) {
		ath_rate_ctl(sc, &an->an_node);
		amn->amn_ticks = ticks;
	}
}