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
struct onoe_node {scalar_t__ on_interval; scalar_t__ on_ticks; int /*<<< orphan*/  on_tx_retr; int /*<<< orphan*/  on_tx_err; int /*<<< orphan*/  on_tx_ok; } ;
struct ath_tx_status {scalar_t__ ts_status; scalar_t__ ts_longretry; scalar_t__ ts_shortretry; } ;
struct ath_softc {int dummy; } ;
struct ath_rc_series {int dummy; } ;
struct ath_node {int /*<<< orphan*/  an_node; } ;

/* Variables and functions */
 struct onoe_node* ATH_NODE_ONOE (struct ath_node*) ; 
 int /*<<< orphan*/  ath_rate_ctl (struct ath_softc*,int /*<<< orphan*/ *) ; 
 scalar_t__ ticks ; 

void
ath_rate_tx_complete(struct ath_softc *sc, struct ath_node *an,
	const struct ath_rc_series *rc, const struct ath_tx_status *ts,
	int frame_size, int nframes, int nbad)
{
	struct onoe_node *on = ATH_NODE_ONOE(an);

	if (ts->ts_status == 0)
		on->on_tx_ok++;
	else
		on->on_tx_err++;
	on->on_tx_retr += ts->ts_shortretry
			+ ts->ts_longretry;
	if (on->on_interval != 0 && ticks - on->on_ticks > on->on_interval) {
		ath_rate_ctl(sc, &an->an_node);
		on->on_ticks = ticks;
	}
}