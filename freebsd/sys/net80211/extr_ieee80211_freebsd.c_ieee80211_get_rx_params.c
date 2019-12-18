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
struct ieee80211_rx_stats {int dummy; } ;
struct ieee80211_rx_params {int /*<<< orphan*/  params; } ;

/* Variables and functions */
 int /*<<< orphan*/  MTAG_ABI_NET80211 ; 
 int /*<<< orphan*/  NET80211_TAG_RECV_PARAMS ; 
 struct m_tag* m_tag_locate (struct mbuf*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (struct ieee80211_rx_stats*,int /*<<< orphan*/ *,int) ; 

int
ieee80211_get_rx_params(struct mbuf *m, struct ieee80211_rx_stats *rxs)
{
	struct m_tag *mtag;
	struct ieee80211_rx_params *rx;

	mtag = m_tag_locate(m, MTAG_ABI_NET80211, NET80211_TAG_RECV_PARAMS,
	    NULL);
	if (mtag == NULL)
		return (-1);
	rx = (struct ieee80211_rx_params *)(mtag + 1);
	memcpy(rxs, &rx->params, sizeof(*rxs));
	return (0);
}