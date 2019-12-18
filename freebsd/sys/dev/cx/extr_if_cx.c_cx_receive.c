#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {scalar_t__ rcvif; } ;
struct mbuf {TYPE_2__ m_pkthdr; } ;
struct TYPE_10__ {int /*<<< orphan*/  queue; scalar_t__ ifp; int /*<<< orphan*/  hook; int /*<<< orphan*/  running; int /*<<< orphan*/  intr_action; int /*<<< orphan*/  aqueue; TYPE_1__* tty; } ;
typedef  TYPE_3__ drv_t ;
struct TYPE_11__ {scalar_t__ mode; int debug; int /*<<< orphan*/  ierrs; TYPE_3__* sys; } ;
typedef  TYPE_4__ cx_chan_t ;
typedef  int /*<<< orphan*/  async_q ;
struct TYPE_8__ {int t_state; } ;

/* Variables and functions */
 int AQ_GSZ (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  AQ_PUSH (int /*<<< orphan*/ *,unsigned char) ; 
 int BF_SZ ; 
 int /*<<< orphan*/  BPF_MTAP (scalar_t__,struct mbuf*) ; 
 int /*<<< orphan*/  CX_DEBUG (TYPE_3__*,char*) ; 
 int /*<<< orphan*/  CX_OVERRUN ; 
 int /*<<< orphan*/  CX_READ ; 
 int /*<<< orphan*/  IFCOUNTER_IPACKETS ; 
 int /*<<< orphan*/  IFCOUNTER_IQDROPS ; 
 int /*<<< orphan*/  IF_ENQUEUE (int /*<<< orphan*/ *,struct mbuf*) ; 
 int MY_SOFT_INTR ; 
 scalar_t__ M_ASYNC ; 
 int /*<<< orphan*/  NG_SEND_DATA_ONLY (int,int /*<<< orphan*/ ,struct mbuf*) ; 
 int TS_ISOPEN ; 
 int /*<<< orphan*/  cx_error (TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cx_fast_ih ; 
 int /*<<< orphan*/  if_inc_counter (scalar_t__,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  m_print (struct mbuf*,int /*<<< orphan*/ ) ; 
 struct mbuf* makembuf (char*,int) ; 
 int /*<<< orphan*/  swi_sched (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void cx_receive (cx_chan_t *c, char *data, int len)
{
	drv_t *d = c->sys;
	struct mbuf *m;
	char *cc = data;
#ifdef NETGRAPH
	int error;
#endif

	if (!d)
		return;
		
	if (c->mode == M_ASYNC && d->tty) {
		if (d->tty->t_state & TS_ISOPEN) {
			async_q *q = &d->aqueue;
			int size = BF_SZ - 1 - AQ_GSZ (q);

			if (len <= 0 && !size)
				return;

			if (len > size) {
				c->ierrs++;
				cx_error (c, CX_OVERRUN);
				len = size - 1;
			}

			while (len--) {
				AQ_PUSH (q, *(unsigned char *)cc);
				cc++;
			}

			d->intr_action |= CX_READ;
			MY_SOFT_INTR = 1;
			swi_sched (cx_fast_ih, 0);
		}
		return;
	}
	if (! d->running)
		return;

	m = makembuf (data, len);
	if (! m) {
		CX_DEBUG (d, ("no memory for packet\n"));
#ifndef NETGRAPH
		if_inc_counter(d->ifp, IFCOUNTER_IQDROPS, 1);
#endif
		return;
	}
	if (c->debug > 1)
		m_print (m, 0);
#ifdef NETGRAPH
	m->m_pkthdr.rcvif = 0;
	NG_SEND_DATA_ONLY (error, d->hook, m);
#else
	if_inc_counter(d->ifp, IFCOUNTER_IPACKETS, 1);
	m->m_pkthdr.rcvif = d->ifp;
	/* Check if there's a BPF listener on this interface.
	 * If so, hand off the raw packet to bpf. */
	BPF_MTAP(d->ifp, m);
	IF_ENQUEUE (&d->queue, m);
#endif
}