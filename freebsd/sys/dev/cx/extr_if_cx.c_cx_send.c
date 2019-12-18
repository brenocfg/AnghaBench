#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u_short ;
typedef  int /*<<< orphan*/  u_char ;
struct mbuf {int /*<<< orphan*/  m_next; } ;
struct TYPE_6__ {int timeout; TYPE_2__* ifp; int /*<<< orphan*/  chan; int /*<<< orphan*/  lo_queue; int /*<<< orphan*/  hi_queue; int /*<<< orphan*/  running; } ;
typedef  TYPE_1__ drv_t ;
struct TYPE_7__ {int /*<<< orphan*/  if_drv_flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  BPF_MTAP (TYPE_2__*,struct mbuf*) ; 
 int /*<<< orphan*/  CX_DEBUG2 (TYPE_1__*,char*) ; 
 int DMABUFSZ ; 
 int /*<<< orphan*/  IFF_DRV_OACTIVE ; 
 int /*<<< orphan*/  IF_DEQUEUE (int /*<<< orphan*/ *,struct mbuf*) ; 
 int /*<<< orphan*/  caddr_t ; 
 scalar_t__ cx_buf_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cx_get_dsr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cx_get_loop (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cx_send_packet (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  m_copydata (struct mbuf*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  m_freem (struct mbuf*) ; 
 int /*<<< orphan*/  m_length (struct mbuf*,int /*<<< orphan*/ *) ; 
 scalar_t__ mtod (struct mbuf*,int /*<<< orphan*/ ) ; 
 struct mbuf* sppp_dequeue (TYPE_2__*) ; 

__attribute__((used)) static void cx_send (drv_t *d)
{
	struct mbuf *m;
	u_short len;

	CX_DEBUG2 (d, ("cx_send\n"));

	/* No output if the interface is down. */
	if (! d->running)
		return;

	/* No output if the modem is off. */
	if (! cx_get_dsr (d->chan) && ! cx_get_loop(d->chan))
		return;

	if (cx_buf_free (d->chan)) {
		/* Get the packet to send. */
#ifdef NETGRAPH
		IF_DEQUEUE (&d->hi_queue, m);
		if (! m)
			IF_DEQUEUE (&d->lo_queue, m);
#else
		m = sppp_dequeue (d->ifp);
#endif
		if (! m)
			return;
#ifndef NETGRAPH
		BPF_MTAP (d->ifp, m);
#endif
		len = m_length (m, NULL);
		if (! m->m_next)
			cx_send_packet (d->chan, (u_char*)mtod (m, caddr_t),
				len, 0);
		else {
			u_char buf [DMABUFSZ];
			m_copydata (m, 0, len, buf);
			cx_send_packet (d->chan, buf, len, 0);
		}
		m_freem (m);

		/* Set up transmit timeout, 10 seconds. */
		d->timeout = 10;
	}
#ifndef NETGRAPH
	d->ifp->if_drv_flags |= IFF_DRV_OACTIVE;
#endif
}