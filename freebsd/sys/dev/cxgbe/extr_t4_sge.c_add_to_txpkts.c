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
struct txpkts {int wr_type; int plen; int len16; int /*<<< orphan*/  npkt; } ;
struct TYPE_2__ {int len; } ;
struct mbuf {TYPE_1__ m_pkthdr; } ;

/* Variables and functions */
 int EQ_ESIZE ; 
 int /*<<< orphan*/  MPASS (int) ; 
 int SGE_MAX_WR_NDESC ; 
 scalar_t__ cannot_use_txpkts (struct mbuf*) ; 
 int howmany (int,int) ; 
 int mbuf_nsegs (struct mbuf*) ; 
 int /*<<< orphan*/  set_mbuf_len16 (struct mbuf*,int) ; 
 int txpkts0_len16 (int) ; 
 int txpkts1_len16 () ; 

__attribute__((used)) static int
add_to_txpkts(struct mbuf *m, struct txpkts *txp, u_int available)
{
	u_int plen, len16, needed, nsegs;

	MPASS(txp->wr_type == 0 || txp->wr_type == 1);

	if (cannot_use_txpkts(m))
		return (1);

	nsegs = mbuf_nsegs(m);
	if (txp->wr_type == 1 && nsegs != 1)
		return (1);

	plen = txp->plen + m->m_pkthdr.len;
	if (plen > 65535)
		return (1);

	if (txp->wr_type == 0)
		len16 = txpkts0_len16(nsegs);
	else
		len16 = txpkts1_len16();
	needed = howmany(txp->len16 + len16, EQ_ESIZE / 16);
	if (needed > SGE_MAX_WR_NDESC || needed > available)
		return (1);

	txp->npkt++;
	txp->plen = plen;
	txp->len16 += len16;
	set_mbuf_len16(m, len16);

	return (0);
}