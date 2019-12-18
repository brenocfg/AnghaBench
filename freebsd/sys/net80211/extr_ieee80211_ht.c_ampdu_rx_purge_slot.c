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

/* Variables and functions */
 int /*<<< orphan*/  m_freem (struct mbuf*) ; 

__attribute__((used)) static void
ampdu_rx_purge_slot(struct ieee80211_rx_ampdu *rap, int i)
{
	struct mbuf *m;

	m = rap->rxa_m[i];
	if (m == NULL)
		return;

	rap->rxa_m[i] = NULL;
	rap->rxa_qbytes -= m->m_pkthdr.len;
	rap->rxa_qframes--;
	m_freem(m);
}