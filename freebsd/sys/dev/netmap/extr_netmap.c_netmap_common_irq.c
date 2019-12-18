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
typedef  size_t u_int ;
struct netmap_kring {scalar_t__ nr_mode; int (* nm_notify ) (struct netmap_kring*,int /*<<< orphan*/ ) ;int /*<<< orphan*/  nr_kflags; } ;
struct netmap_adapter {int dummy; } ;
typedef  enum txrx { ____Placeholder_txrx } txrx ;

/* Variables and functions */
 size_t NETMAP_RING_MASK ; 
 scalar_t__ NKR_NETMAP_OFF ; 
 int /*<<< orphan*/  NKR_PENDINTR ; 
 struct netmap_kring** NMR (struct netmap_adapter*,int) ; 
 int NM_DEBUG_RXINTR ; 
 int NM_DEBUG_TXINTR ; 
 int NM_IRQ_PASS ; 
 int NR_RX ; 
 int NR_TX ; 
 int netmap_debug ; 
 int /*<<< orphan*/  nm_prlim (int,char*,char*,size_t) ; 
 size_t nma_get_nrings (struct netmap_adapter*,int) ; 
 int stub1 (struct netmap_kring*,int /*<<< orphan*/ ) ; 

int
netmap_common_irq(struct netmap_adapter *na, u_int q, u_int *work_done)
{
	struct netmap_kring *kring;
	enum txrx t = (work_done ? NR_RX : NR_TX);

	q &= NETMAP_RING_MASK;

	if (netmap_debug & (NM_DEBUG_RXINTR|NM_DEBUG_TXINTR)) {
	        nm_prlim(5, "received %s queue %d", work_done ? "RX" : "TX" , q);
	}

	if (q >= nma_get_nrings(na, t))
		return NM_IRQ_PASS; // not a physical queue

	kring = NMR(na, t)[q];

	if (kring->nr_mode == NKR_NETMAP_OFF) {
		return NM_IRQ_PASS;
	}

	if (t == NR_RX) {
		kring->nr_kflags |= NKR_PENDINTR;	// XXX atomic ?
		*work_done = 1; /* do not fire napi again */
	}

	return kring->nm_notify(kring, 0);
}