#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  size_t u_int ;
struct netmap_kring {scalar_t__ nr_mode; int /*<<< orphan*/  rx_queue; } ;
struct netmap_generic_adapter {TYPE_1__* mit; int /*<<< orphan*/  rxsg; } ;
struct netmap_adapter {size_t num_rx_rings; struct netmap_kring** rx_rings; } ;
struct mbuf {int dummy; } ;
struct ifnet {int dummy; } ;
struct TYPE_3__ {int mit_pending; } ;

/* Variables and functions */
 scalar_t__ MBUF_LEN (struct mbuf*) ; 
 size_t MBUF_RXQ (struct mbuf*) ; 
 struct netmap_adapter* NA (struct ifnet*) ; 
 scalar_t__ NETMAP_BUF_SIZE (struct netmap_adapter*) ; 
 scalar_t__ NKR_NETMAP_OFF ; 
 scalar_t__ likely (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  m_freem (struct mbuf*) ; 
 int mbq_len (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mbq_safe_enqueue (int /*<<< orphan*/ *,struct mbuf*) ; 
 int /*<<< orphan*/  netmap_generic_irq (struct netmap_adapter*,size_t,size_t*) ; 
 int netmap_generic_mit ; 
 int /*<<< orphan*/  nm_os_mitigation_active (TYPE_1__*) ; 
 int /*<<< orphan*/  nm_os_mitigation_start (TYPE_1__*) ; 
 int /*<<< orphan*/  nm_prlim (int,char*,int) ; 
 scalar_t__ unlikely (int) ; 

int
generic_rx_handler(struct ifnet *ifp, struct mbuf *m)
{
	struct netmap_adapter *na = NA(ifp);
	struct netmap_generic_adapter *gna = (struct netmap_generic_adapter *)na;
	struct netmap_kring *kring;
	u_int work_done;
	u_int r = MBUF_RXQ(m); /* receive ring number */

	if (r >= na->num_rx_rings) {
		r = r % na->num_rx_rings;
	}

	kring = na->rx_rings[r];

	if (kring->nr_mode == NKR_NETMAP_OFF) {
		/* We must not intercept this mbuf. */
		return 0;
	}

	/* limit the size of the queue */
	if (unlikely(!gna->rxsg && MBUF_LEN(m) > NETMAP_BUF_SIZE(na))) {
		/* This may happen when GRO/LRO features are enabled for
		 * the NIC driver when the generic adapter does not
		 * support RX scatter-gather. */
		nm_prlim(2, "Warning: driver pushed up big packet "
				"(size=%d)", (int)MBUF_LEN(m));
		m_freem(m);
	} else if (unlikely(mbq_len(&kring->rx_queue) > 1024)) {
		m_freem(m);
	} else {
		mbq_safe_enqueue(&kring->rx_queue, m);
	}

	if (netmap_generic_mit < 32768) {
		/* no rx mitigation, pass notification up */
		netmap_generic_irq(na, r, &work_done);
	} else {
		/* same as send combining, filter notification if there is a
		 * pending timer, otherwise pass it up and start a timer.
		 */
		if (likely(nm_os_mitigation_active(&gna->mit[r]))) {
			/* Record that there is some pending work. */
			gna->mit[r].mit_pending = 1;
		} else {
			netmap_generic_irq(na, r, &work_done);
			nm_os_mitigation_start(&gna->mit[r]);
		}
	}

	/* We have intercepted the mbuf. */
	return 1;
}