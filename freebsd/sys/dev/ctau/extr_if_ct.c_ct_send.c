#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u_short ;
typedef  int /*<<< orphan*/  u_char ;
struct mbuf {int /*<<< orphan*/  m_next; } ;
struct TYPE_10__ {int timeout; TYPE_2__* ifp; TYPE_3__* chan; int /*<<< orphan*/  queue; int /*<<< orphan*/  hi_queue; int /*<<< orphan*/  running; } ;
typedef  TYPE_1__ drv_t ;
struct TYPE_12__ {size_t te; int /*<<< orphan*/ ** tbuf; int /*<<< orphan*/  tn; } ;
struct TYPE_11__ {int /*<<< orphan*/  if_drv_flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  BPF_MTAP (TYPE_2__*,struct mbuf*) ; 
 int /*<<< orphan*/  CT_DEBUG2 (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  IFF_DRV_OACTIVE ; 
 int /*<<< orphan*/  IF_DEQUEUE (int /*<<< orphan*/ *,struct mbuf*) ; 
 int /*<<< orphan*/  caddr_t ; 
 scalar_t__ ct_buf_free (TYPE_3__*) ; 
 int /*<<< orphan*/  ct_get_dsr (TYPE_3__*) ; 
 int /*<<< orphan*/  ct_get_loop (TYPE_3__*) ; 
 int /*<<< orphan*/  ct_send_packet (TYPE_3__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  m_copydata (struct mbuf*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  m_freem (struct mbuf*) ; 
 int /*<<< orphan*/  m_length (struct mbuf*,int /*<<< orphan*/ *) ; 
 scalar_t__ mtod (struct mbuf*,int /*<<< orphan*/ ) ; 
 struct mbuf* sppp_dequeue (TYPE_2__*) ; 

__attribute__((used)) static void ct_send (drv_t *d)
{
	struct mbuf *m;
	u_short len;

	CT_DEBUG2 (d, ("ct_send, tn=%d\n", d->chan->tn));

	/* No output if the interface is down. */
	if (! d->running)
		return;

	/* No output if the modem is off. */
	if (! ct_get_dsr (d->chan) && !ct_get_loop (d->chan))
		return;

	while (ct_buf_free (d->chan)) {
		/* Get the packet to send. */
#ifdef NETGRAPH
		IF_DEQUEUE (&d->hi_queue, m);
		if (! m)
			IF_DEQUEUE (&d->queue, m);
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
			ct_send_packet (d->chan, (u_char*)mtod (m, caddr_t),
				len, 0);
		else {
			m_copydata (m, 0, len, d->chan->tbuf[d->chan->te]);
			ct_send_packet (d->chan, d->chan->tbuf[d->chan->te],
				len, 0);
		}
		m_freem (m);

		/* Set up transmit timeout, if the transmit ring is not empty.
		 * Transmit timeout is 10 seconds. */
		d->timeout = 10;
	}
#ifndef NETGRAPH
	d->ifp->if_drv_flags |= IFF_DRV_OACTIVE;
#endif
}