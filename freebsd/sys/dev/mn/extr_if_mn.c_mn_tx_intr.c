#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u_int32_t ;
struct trxd {struct trxd* vnext; struct mbuf* m; } ;
struct TYPE_4__ {scalar_t__* ctxd; } ;
struct mn_softc {char* name; TYPE_3__** ch; TYPE_1__ m32_mem; } ;
struct TYPE_5__ {int len; } ;
struct mbuf {TYPE_2__ m_pkthdr; } ;
struct TYPE_6__ {scalar_t__ state; int tx_pending; struct trxd* x1; int /*<<< orphan*/  last_xmit; } ;

/* Variables and functions */
 scalar_t__ UP ; 
 int /*<<< orphan*/  m_freem (struct mbuf*) ; 
 int /*<<< orphan*/  mn_free_desc (struct trxd*) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  time_second ; 
 scalar_t__ vtophys (struct trxd*) ; 

__attribute__((used)) static void
mn_tx_intr(struct mn_softc *sc, u_int32_t vector)
{
	u_int32_t chan;
	struct trxd *dp;
	struct mbuf *m;

	chan = vector & 0x1f;
	if (!sc->ch[chan]) 
		return;
	if (sc->ch[chan]->state != UP) {
		printf("%s: tx_intr when not UP\n", sc->name);
		return;
	}
	for (;;) {
		dp = sc->ch[chan]->x1;
		if (vtophys(dp) == sc->m32_mem.ctxd[chan]) 
			return;
		m = dp->m;
		if (m) {
#if 0
			printf("%d = %d - %d (%p)\n",
			    sc->ch[chan]->tx_pending - m->m_pkthdr.len,
			    sc->ch[chan]->tx_pending , m->m_pkthdr.len, m);
#endif
			sc->ch[chan]->tx_pending -= m->m_pkthdr.len;
			m_freem(m);
		}
		sc->ch[chan]->last_xmit = time_second;
		sc->ch[chan]->x1 = dp->vnext;
		mn_free_desc(dp);
	}
}