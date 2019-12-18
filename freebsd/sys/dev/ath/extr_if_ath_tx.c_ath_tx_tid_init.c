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
struct TYPE_2__ {int /*<<< orphan*/  tid_q; } ;
struct ath_tid {int tid; int /*<<< orphan*/  ac; scalar_t__ cleanup_inprogress; scalar_t__ hwq_depth; scalar_t__ sched; scalar_t__ paused; scalar_t__ baw_tail; scalar_t__ baw_head; int /*<<< orphan*/ ** tx_buf; struct ath_node* an; TYPE_1__ filtq; int /*<<< orphan*/  tid_q; } ;
struct ath_softc {int dummy; } ;
struct ath_node {int clrdmask; struct ath_tid* an_tid; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATH_NONQOS_TID_AC ; 
 int ATH_TID_MAX_BUFS ; 
 int IEEE80211_NONQOS_TID ; 
 int IEEE80211_TID_SIZE ; 
 int /*<<< orphan*/  TAILQ_INIT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TID_TO_WME_AC (int) ; 
 int /*<<< orphan*/  bzero (struct ath_tid*,int) ; 

void
ath_tx_tid_init(struct ath_softc *sc, struct ath_node *an)
{
	int i, j;
	struct ath_tid *atid;

	for (i = 0; i < IEEE80211_TID_SIZE; i++) {
		atid = &an->an_tid[i];

		/* XXX now with this bzer(), is the field 0'ing needed? */
		bzero(atid, sizeof(*atid));

		TAILQ_INIT(&atid->tid_q);
		TAILQ_INIT(&atid->filtq.tid_q);
		atid->tid = i;
		atid->an = an;
		for (j = 0; j < ATH_TID_MAX_BUFS; j++)
			atid->tx_buf[j] = NULL;
		atid->baw_head = atid->baw_tail = 0;
		atid->paused = 0;
		atid->sched = 0;
		atid->hwq_depth = 0;
		atid->cleanup_inprogress = 0;
		if (i == IEEE80211_NONQOS_TID)
			atid->ac = ATH_NONQOS_TID_AC;
		else
			atid->ac = TID_TO_WME_AC(i);
	}
	an->clrdmask = 1;	/* Always start by setting this bit */
}