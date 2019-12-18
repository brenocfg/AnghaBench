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
struct xnb_pkt {int dummy; } ;
struct mbuf {scalar_t__ m_len; } ;

/* Variables and functions */
 int /*<<< orphan*/  MT_DATA ; 
 int /*<<< orphan*/  M_WAITOK ; 
 int /*<<< orphan*/  XNB_ASSERT (int) ; 
 struct mbuf* m_get (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  safe_m_freem (struct mbuf**) ; 
 int /*<<< orphan*/  xnb_mbufc2pkt (struct mbuf*,struct xnb_pkt*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  xnb_pkt_is_valid (struct xnb_pkt*) ; 

__attribute__((used)) static void
xnb_mbufc2pkt_empty(char *buffer, size_t buflen) {
	struct xnb_pkt pkt;
	int free_slots = 64;
	struct mbuf *mbuf;

	mbuf = m_get(M_WAITOK, MT_DATA);
	/*
	 * note: it is illegal to set M_PKTHDR on a mbuf with no data.  Doing so
	 * will cause m_freem to segfault
	 */
	XNB_ASSERT(mbuf->m_len == 0);

	xnb_mbufc2pkt(mbuf, &pkt, 0, free_slots);
	XNB_ASSERT(! xnb_pkt_is_valid(&pkt));

	safe_m_freem(&mbuf);
}