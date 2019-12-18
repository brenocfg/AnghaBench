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
struct ieee80211_ageq {scalar_t__ aq_len; int /*<<< orphan*/ * aq_tail; struct mbuf* aq_head; } ;

/* Variables and functions */
 int /*<<< orphan*/  IEEE80211_AGEQ_LOCK (struct ieee80211_ageq*) ; 
 int /*<<< orphan*/  IEEE80211_AGEQ_UNLOCK (struct ieee80211_ageq*) ; 
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int M_AGE_GET (struct mbuf*) ; 
 int /*<<< orphan*/  M_AGE_SUB (struct mbuf*,int) ; 

struct mbuf *
ieee80211_ageq_age(struct ieee80211_ageq *aq, int quanta)
{
	struct mbuf *head, **phead;
	struct mbuf *m;

	phead = &head;
	if (aq->aq_len != 0) {
		IEEE80211_AGEQ_LOCK(aq);
		while ((m = aq->aq_head) != NULL && M_AGE_GET(m) < quanta) {
			if ((aq->aq_head = m->m_nextpkt) == NULL)
				aq->aq_tail = NULL;
			KASSERT(aq->aq_len > 0, ("aq len %d", aq->aq_len));
			aq->aq_len--;
			/* add to private list for return */
			*phead = m;
			phead = &m->m_nextpkt;
		}
		if (m != NULL)
			M_AGE_SUB(m, quanta);
		IEEE80211_AGEQ_UNLOCK(aq);
	}
	*phead = NULL;
	return head;
}