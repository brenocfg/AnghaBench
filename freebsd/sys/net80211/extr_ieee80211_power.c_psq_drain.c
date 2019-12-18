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
struct mbuf {struct mbuf* m_nextpkt; } ;
struct ieee80211_psq_head {scalar_t__ len; int /*<<< orphan*/ * tail; struct mbuf* head; } ;
struct ieee80211_psq {int psq_len; struct ieee80211_psq_head* psq_head; } ;

/* Variables and functions */
 int /*<<< orphan*/  IEEE80211_PSQ_LOCK (struct ieee80211_psq*) ; 
 int /*<<< orphan*/  IEEE80211_PSQ_UNLOCK (struct ieee80211_psq*) ; 
 int /*<<< orphan*/  psq_mfree (struct mbuf*) ; 

__attribute__((used)) static int
psq_drain(struct ieee80211_psq *psq)
{
	struct ieee80211_psq_head *qhead;
	struct mbuf *m;
	int qlen;

	IEEE80211_PSQ_LOCK(psq);
	qlen = psq->psq_len;
	qhead = &psq->psq_head[0];
again:
	while ((m = qhead->head) != NULL) {
		qhead->head = m->m_nextpkt;
		psq_mfree(m);
	}
	qhead->tail = NULL;
	qhead->len = 0;
	if (qhead == &psq->psq_head[0]) {	/* Algol-68 style for loop */
		qhead = &psq->psq_head[1];
		goto again;
	}
	psq->psq_len = 0;
	IEEE80211_PSQ_UNLOCK(psq);

	return qlen;
}