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
struct mbuf {int /*<<< orphan*/  m_flags; } ;
struct m_tag {int dummy; } ;
struct ieee80211_cb {void (* func ) (struct ieee80211_node*,void*,int) ;void* arg; } ;

/* Variables and functions */
 int /*<<< orphan*/  MTAG_ABI_NET80211 ; 
 int /*<<< orphan*/  M_NOWAIT ; 
 int /*<<< orphan*/  M_TXCB ; 
 int /*<<< orphan*/  NET80211_TAG_CALLBACK ; 
 struct m_tag* m_tag_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  m_tag_prepend (struct mbuf*,struct m_tag*) ; 

int
ieee80211_add_callback(struct mbuf *m,
	void (*func)(struct ieee80211_node *, void *, int), void *arg)
{
	struct m_tag *mtag;
	struct ieee80211_cb *cb;

	mtag = m_tag_alloc(MTAG_ABI_NET80211, NET80211_TAG_CALLBACK,
			sizeof(struct ieee80211_cb), M_NOWAIT);
	if (mtag == NULL)
		return 0;

	cb = (struct ieee80211_cb *)(mtag+1);
	cb->func = func;
	cb->arg = arg;
	m_tag_prepend(m, mtag);
	m->m_flags |= M_TXCB;
	return 1;
}