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
struct mbuf {int m_flags; struct mbuf* m_nextpkt; int /*<<< orphan*/  m_len; } ;
struct ieee80211vap {int /*<<< orphan*/  (* iv_set_tim ) (struct ieee80211_node*,int) ;} ;
struct ieee80211com {int ic_bintval; } ;
struct ieee80211_psq_head {int /*<<< orphan*/  len; struct mbuf* tail; struct mbuf* head; } ;
struct ieee80211_psq {int psq_len; int psq_maxlen; int psq_drops; struct ieee80211_psq_head* psq_head; } ;
struct ieee80211_node {int ni_intval; struct ieee80211com* ni_ic; struct ieee80211vap* ni_vap; struct ieee80211_psq ni_psq; } ;

/* Variables and functions */
 int ENOSPC ; 
 int /*<<< orphan*/  IEEE80211_MSG_ANY ; 
 int /*<<< orphan*/  IEEE80211_MSG_POWER ; 
 int /*<<< orphan*/  IEEE80211_NOTE (struct ieee80211vap*,int /*<<< orphan*/ ,struct ieee80211_node*,char*,int,int) ; 
 int /*<<< orphan*/  IEEE80211_PSQ_LOCK (struct ieee80211_psq*) ; 
 int /*<<< orphan*/  IEEE80211_PSQ_UNLOCK (struct ieee80211_psq*) ; 
 int IEEE80211_TU_TO_MS (int) ; 
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int M_AGE_GET (struct mbuf*) ; 
 int /*<<< orphan*/  M_AGE_SET (struct mbuf*,int) ; 
 int M_ENCAP ; 
 int /*<<< orphan*/  caddr_t ; 
 int /*<<< orphan*/  ieee80211_dump_pkt (struct ieee80211com*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 scalar_t__ ieee80211_msg_dumppkts (struct ieee80211vap*) ; 
 int /*<<< orphan*/  mtod (struct mbuf*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  psq_mfree (struct mbuf*) ; 
 int /*<<< orphan*/  stub1 (struct ieee80211_node*,int) ; 

int
ieee80211_pwrsave(struct ieee80211_node *ni, struct mbuf *m)
{
	struct ieee80211_psq *psq = &ni->ni_psq;
	struct ieee80211vap *vap = ni->ni_vap;
	struct ieee80211com *ic = ni->ni_ic;
	struct ieee80211_psq_head *qhead;
	int qlen, age;

	IEEE80211_PSQ_LOCK(psq);
	if (psq->psq_len >= psq->psq_maxlen) {
		psq->psq_drops++;
		IEEE80211_PSQ_UNLOCK(psq);
		IEEE80211_NOTE(vap, IEEE80211_MSG_ANY, ni,
		    "pwr save q overflow, drops %d (size %d)",
		    psq->psq_drops, psq->psq_len);
#ifdef IEEE80211_DEBUG
		if (ieee80211_msg_dumppkts(vap))
			ieee80211_dump_pkt(ni->ni_ic, mtod(m, caddr_t),
			    m->m_len, -1, -1);
#endif
		psq_mfree(m);
		return ENOSPC;
	}
	/*
	 * Tag the frame with it's expiry time and insert it in
	 * the appropriate queue.  The aging interval is 4 times
	 * the listen interval specified by the station. Frames
	 * that sit around too long are reclaimed using this
	 * information.
	 */
	/* TU -> secs.  XXX handle overflow? */
	age = IEEE80211_TU_TO_MS((ni->ni_intval * ic->ic_bintval) << 2) / 1000;
	/*
	 * Encapsulated frames go on the high priority queue,
	 * other stuff goes on the low priority queue.  We use
	 * this to order frames returned out of the driver
	 * ahead of frames we collect in ieee80211_start.
	 */
	if (m->m_flags & M_ENCAP)
		qhead = &psq->psq_head[0];
	else
		qhead = &psq->psq_head[1];
	if (qhead->tail == NULL) {
		struct mbuf *mh;

		qhead->head = m;
		/*
		 * Take care to adjust age when inserting the first
		 * frame of a queue and the other queue already has
		 * frames.  We need to preserve the age difference
		 * relationship so ieee80211_node_psq_age works.
		 */
		if (qhead == &psq->psq_head[1]) {
			mh = psq->psq_head[0].head;
			if (mh != NULL)
				age-= M_AGE_GET(mh);
		} else {
			mh = psq->psq_head[1].head;
			if (mh != NULL) {
				int nage = M_AGE_GET(mh) - age;
				/* XXX is clamping to zero good 'nuf? */
				M_AGE_SET(mh, nage < 0 ? 0 : nage);
			}
		}
	} else {
		qhead->tail->m_nextpkt = m;
		age -= M_AGE_GET(qhead->head);
	}
	KASSERT(age >= 0, ("age %d", age));
	M_AGE_SET(m, age);
	m->m_nextpkt = NULL;
	qhead->tail = m;
	qhead->len++;
	qlen = ++(psq->psq_len);
	IEEE80211_PSQ_UNLOCK(psq);

	IEEE80211_NOTE(vap, IEEE80211_MSG_POWER, ni,
	    "save frame with age %d, %u now queued", age, qlen);

	if (qlen == 1 && vap->iv_set_tim != NULL)
		vap->iv_set_tim(ni, 1);

	return 0;
}