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
struct TYPE_2__ {scalar_t__ len; } ;
struct mbuf {TYPE_1__ m_pkthdr; } ;
struct ieee80211_rx_ampdu {int /*<<< orphan*/  rxa_qframes; int /*<<< orphan*/  rxa_qbytes; struct mbuf** rxa_m; } ;
struct ieee80211_node {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ampdu_dispatch (struct ieee80211_node*,struct mbuf*) ; 

__attribute__((used)) static int
ampdu_dispatch_slot(struct ieee80211_rx_ampdu *rap, struct ieee80211_node *ni,
    int i)
{
	struct mbuf *m;

	if (rap->rxa_m[i] == NULL)
		return (0);

	m = rap->rxa_m[i];
	rap->rxa_m[i] = NULL;
	rap->rxa_qbytes -= m->m_pkthdr.len;
	rap->rxa_qframes--;

	ampdu_dispatch(ni, m);

	return (1);
}