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
struct mbuf {int dummy; } ;
struct m_tag {int dummy; } ;
struct ieee80211_node {int dummy; } ;
struct ieee80211_cb {int /*<<< orphan*/  arg; int /*<<< orphan*/  (* func ) (struct ieee80211_node*,int /*<<< orphan*/ ,int) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  MTAG_ABI_NET80211 ; 
 int /*<<< orphan*/  NET80211_TAG_CALLBACK ; 
 struct m_tag* m_tag_locate (struct mbuf*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct ieee80211_node*,int /*<<< orphan*/ ,int) ; 

void
ieee80211_process_callback(struct ieee80211_node *ni,
	struct mbuf *m, int status)
{
	struct m_tag *mtag;

	mtag = m_tag_locate(m, MTAG_ABI_NET80211, NET80211_TAG_CALLBACK, NULL);
	if (mtag != NULL) {
		struct ieee80211_cb *cb = (struct ieee80211_cb *)(mtag+1);
		cb->func(ni, cb->arg, status);
	}
}