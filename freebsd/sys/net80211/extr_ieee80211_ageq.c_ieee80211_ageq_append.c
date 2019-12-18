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
struct ieee80211_ageq {scalar_t__ aq_len; scalar_t__ aq_maxlen; int /*<<< orphan*/  aq_drops; struct mbuf* aq_tail; struct mbuf* aq_head; } ;

/* Variables and functions */
 int ENOSPC ; 
 int /*<<< orphan*/  IEEE80211_AGEQ_LOCK (struct ieee80211_ageq*) ; 
 int /*<<< orphan*/  IEEE80211_AGEQ_UNLOCK (struct ieee80211_ageq*) ; 
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 scalar_t__ M_AGE_GET (struct mbuf*) ; 
 int /*<<< orphan*/  M_AGE_SET (struct mbuf*,int) ; 
 scalar_t__ __predict_true (int) ; 
 int /*<<< orphan*/  ageq_mfree (struct mbuf*) ; 

int
ieee80211_ageq_append(struct ieee80211_ageq *aq, struct mbuf *m, int age)
{
	IEEE80211_AGEQ_LOCK(aq);
	if (__predict_true(aq->aq_len < aq->aq_maxlen)) {
		if (aq->aq_tail == NULL) {
			aq->aq_head = m;
		} else {
			aq->aq_tail->m_nextpkt = m;
			age -= M_AGE_GET(aq->aq_head);
		}
		KASSERT(age >= 0, ("age %d", age));
		M_AGE_SET(m, age);
		m->m_nextpkt = NULL;
		aq->aq_tail = m;
		aq->aq_len++;
		IEEE80211_AGEQ_UNLOCK(aq);
		return 0;
	} else {
		/*
		 * No space, drop and cleanup references.
		 */
		aq->aq_drops++;
		IEEE80211_AGEQ_UNLOCK(aq);
		/* XXX tail drop? */
		ageq_mfree(m);
		return ENOSPC;
	}
}