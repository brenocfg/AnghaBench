#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ rcvif; } ;
struct mbuf {TYPE_1__ m_pkthdr; } ;
struct TYPE_7__ {int /*<<< orphan*/  queue; scalar_t__ ifp; int /*<<< orphan*/  hook; int /*<<< orphan*/  running; } ;
typedef  TYPE_2__ drv_t ;
struct TYPE_8__ {int debug; TYPE_2__* sys; } ;
typedef  TYPE_3__ cp_chan_t ;

/* Variables and functions */
 int /*<<< orphan*/  BPF_MTAP (scalar_t__,struct mbuf*) ; 
 int /*<<< orphan*/  CP_DEBUG (TYPE_2__*,char*) ; 
 int /*<<< orphan*/  IFCOUNTER_IPACKETS ; 
 int /*<<< orphan*/  IFCOUNTER_IQDROPS ; 
 int /*<<< orphan*/  IF_ENQUEUE (int /*<<< orphan*/ *,struct mbuf*) ; 
 int /*<<< orphan*/  NG_SEND_DATA_ONLY (int,int /*<<< orphan*/ ,struct mbuf*) ; 
 int /*<<< orphan*/  if_inc_counter (scalar_t__,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  m_print (struct mbuf*,int /*<<< orphan*/ ) ; 
 struct mbuf* makembuf (unsigned char*,int) ; 

__attribute__((used)) static void cp_receive (cp_chan_t *c, unsigned char *data, int len)
{
	drv_t *d = c->sys;
	struct mbuf *m;
#ifdef NETGRAPH
	int error;
#endif

	if (! d->running)
		return;

	m = makembuf (data, len);
	if (! m) {
		CP_DEBUG (d, ("no memory for packet\n"));
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