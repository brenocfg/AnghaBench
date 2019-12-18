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
struct ieee80211_tx_params {int /*<<< orphan*/  params; } ;
struct ieee80211_bpf_params {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MTAG_ABI_NET80211 ; 
 int /*<<< orphan*/  M_NOWAIT ; 
 int /*<<< orphan*/  NET80211_TAG_XMIT_PARAMS ; 
 struct m_tag* m_tag_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  m_tag_prepend (struct mbuf*,struct m_tag*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,struct ieee80211_bpf_params const*,int) ; 

int
ieee80211_add_xmit_params(struct mbuf *m,
    const struct ieee80211_bpf_params *params)
{
	struct m_tag *mtag;
	struct ieee80211_tx_params *tx;

	mtag = m_tag_alloc(MTAG_ABI_NET80211, NET80211_TAG_XMIT_PARAMS,
	    sizeof(struct ieee80211_tx_params), M_NOWAIT);
	if (mtag == NULL)
		return (0);

	tx = (struct ieee80211_tx_params *)(mtag+1);
	memcpy(&tx->params, params, sizeof(struct ieee80211_bpf_params));
	m_tag_prepend(m, mtag);
	return (1);
}