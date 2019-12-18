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
struct rtwn_softc {int dummy; } ;
struct rtwn_rx_stat_common {int dummy; } ;
struct mbuf {int dummy; } ;
struct ieee80211_node {int dummy; } ;
typedef  int /*<<< orphan*/  stat ;
typedef  int /*<<< orphan*/  caddr_t ;

/* Variables and functions */
 int /*<<< orphan*/  m_adj (struct mbuf*,int) ; 
 int /*<<< orphan*/  m_copydata (struct mbuf*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 struct ieee80211_node* rtwn_rx_common (struct rtwn_softc*,struct mbuf*,struct rtwn_rx_stat_common*) ; 

__attribute__((used)) static struct ieee80211_node *
rtwn_rx_frame(struct rtwn_softc *sc, struct mbuf *m)
{
	struct rtwn_rx_stat_common stat;

	/* Imitate PCIe layout. */
	m_copydata(m, 0, sizeof(stat), (caddr_t)&stat);
	m_adj(m, sizeof(stat));

	return (rtwn_rx_common(sc, m, &stat));
}