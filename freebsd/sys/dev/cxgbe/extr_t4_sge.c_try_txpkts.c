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
typedef  int u_int ;
struct txpkts {int wr_type; int len16; int plen; int npkt; } ;
struct TYPE_2__ {int len; } ;
struct mbuf {TYPE_1__ m_pkthdr; } ;
struct fw_eth_tx_pkts_wr {int dummy; } ;

/* Variables and functions */
 int EQ_ESIZE ; 
 int SGE_MAX_WR_NDESC ; 
 scalar_t__ cannot_use_txpkts (struct mbuf*) ; 
 int howmany (int,int) ; 
 int mbuf_nsegs (struct mbuf*) ; 
 int /*<<< orphan*/  set_mbuf_len16 (struct mbuf*,int) ; 
 int txpkts0_len16 (int) ; 
 int txpkts1_len16 () ; 

__attribute__((used)) static int
try_txpkts(struct mbuf *m, struct mbuf *n, struct txpkts *txp, u_int available)
{
	u_int needed, nsegs1, nsegs2, l1, l2;

	if (cannot_use_txpkts(m) || cannot_use_txpkts(n))
		return (1);

	nsegs1 = mbuf_nsegs(m);
	nsegs2 = mbuf_nsegs(n);
	if (nsegs1 + nsegs2 == 2) {
		txp->wr_type = 1;
		l1 = l2 = txpkts1_len16();
	} else {
		txp->wr_type = 0;
		l1 = txpkts0_len16(nsegs1);
		l2 = txpkts0_len16(nsegs2);
	}
	txp->len16 = howmany(sizeof(struct fw_eth_tx_pkts_wr), 16) + l1 + l2;
	needed = howmany(txp->len16, EQ_ESIZE / 16);
	if (needed > SGE_MAX_WR_NDESC || needed > available)
		return (1);

	txp->plen = m->m_pkthdr.len + n->m_pkthdr.len;
	if (txp->plen > 65535)
		return (1);

	txp->npkt = 2;
	set_mbuf_len16(m, l1);
	set_mbuf_len16(n, l2);

	return (0);
}