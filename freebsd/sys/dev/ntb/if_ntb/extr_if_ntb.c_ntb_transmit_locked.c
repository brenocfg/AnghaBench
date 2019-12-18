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
struct ntb_net_queue {int /*<<< orphan*/  br; int /*<<< orphan*/  queue_full; int /*<<< orphan*/  qp; int /*<<< orphan*/  ifp; } ;
struct TYPE_2__ {int len; } ;
struct mbuf {short m_flags; TYPE_1__ m_pkthdr; } ;
typedef  int /*<<< orphan*/  if_t ;

/* Variables and functions */
 int /*<<< orphan*/  CTR0 (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  CTR1 (int /*<<< orphan*/ ,char*,struct mbuf*) ; 
 int /*<<< orphan*/  CTR2 (int /*<<< orphan*/ ,char*,struct mbuf*,int) ; 
 int EAGAIN ; 
 int /*<<< orphan*/  IFCOUNTER_OBYTES ; 
 int /*<<< orphan*/  IFCOUNTER_OERRORS ; 
 int /*<<< orphan*/  IFCOUNTER_OMCASTS ; 
 int /*<<< orphan*/  IFCOUNTER_OPACKETS ; 
 int /*<<< orphan*/  KTR_NTB ; 
 short M_MCAST ; 
 int SBT_1MS ; 
 int /*<<< orphan*/  callout_reset_sbt (int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ ,struct ntb_net_queue*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drbr_advance (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct mbuf* drbr_peek (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drbr_putback (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct mbuf*) ; 
 int /*<<< orphan*/  if_etherbpfmtap (int /*<<< orphan*/ ,struct mbuf*) ; 
 int /*<<< orphan*/  if_inc_counter (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  m_freem (struct mbuf*) ; 
 int /*<<< orphan*/  ntb_qp_full ; 
 int ntb_transport_tx_enqueue (int /*<<< orphan*/ ,struct mbuf*,struct mbuf*,int) ; 

__attribute__((used)) static void
ntb_transmit_locked(struct ntb_net_queue *q)
{
	if_t ifp = q->ifp;
	struct mbuf *m;
	int rc, len;
	short mflags;

	CTR0(KTR_NTB, "TX: ntb_transmit_locked");
	while ((m = drbr_peek(ifp, q->br)) != NULL) {
		CTR1(KTR_NTB, "TX: start mbuf %p", m);
		if_etherbpfmtap(ifp, m);
		len = m->m_pkthdr.len;
		mflags = m->m_flags;
		rc = ntb_transport_tx_enqueue(q->qp, m, m, len);
		if (rc != 0) {
			CTR2(KTR_NTB, "TX: could not tx mbuf %p: %d", m, rc);
			if (rc == EAGAIN) {
				drbr_putback(ifp, q->br, m);
				callout_reset_sbt(&q->queue_full,
				    SBT_1MS / 4, SBT_1MS / 4,
				    ntb_qp_full, q, 0);
			} else {
				m_freem(m);
				drbr_advance(ifp, q->br);
				if_inc_counter(ifp, IFCOUNTER_OERRORS, 1);
			}
			break;
		}
		drbr_advance(ifp, q->br);
		if_inc_counter(ifp, IFCOUNTER_OPACKETS, 1);
		if_inc_counter(ifp, IFCOUNTER_OBYTES, len);
		if (mflags & M_MCAST)
			if_inc_counter(ifp, IFCOUNTER_OMCASTS, 1);
	}
}