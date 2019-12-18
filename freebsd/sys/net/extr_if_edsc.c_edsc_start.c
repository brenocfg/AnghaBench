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
struct TYPE_2__ {int len; } ;
struct mbuf {TYPE_1__ m_pkthdr; } ;
struct ifnet {int /*<<< orphan*/  if_snd; } ;

/* Variables and functions */
 int /*<<< orphan*/  BPF_MTAP (struct ifnet*,struct mbuf*) ; 
 int /*<<< orphan*/  IFCOUNTER_OBYTES ; 
 int /*<<< orphan*/  IFCOUNTER_OPACKETS ; 
 int /*<<< orphan*/  IFQ_DEQUEUE (int /*<<< orphan*/ *,struct mbuf*) ; 
 int /*<<< orphan*/  if_inc_counter (struct ifnet*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  m_freem (struct mbuf*) ; 

__attribute__((used)) static void
edsc_start(struct ifnet *ifp)
{
	struct mbuf		*m;

	/*
	 * A hardware interface driver can set IFF_DRV_OACTIVE
	 * in ifp->if_drv_flags:
	 *
	 * ifp->if_drv_flags |= IFF_DRV_OACTIVE;
	 *
	 * to prevent if_start from being invoked again while the
	 * transmission is under way.  The flag is to protect the
	 * device's transmitter, not the method itself.  The output
	 * queue is locked and several threads can process it in
	 * parallel safely, so the driver can use other means to
	 * serialize access to the transmitter.
	 *
	 * If using IFF_DRV_OACTIVE, the driver should clear the flag
	 * not earlier than the current transmission is complete, e.g.,
	 * upon an interrupt from the device, not just before returning
	 * from if_start.  This method merely starts the transmission,
	 * which may proceed asynchronously.
	 */

	/*
	 * We loop getting packets from the queue until it's empty.
	 * A h/w driver would loop until the device can accept more
	 * data into its buffer, or while there are free transmit
	 * descriptors, or whatever.
	 */
	for (;;) {
		/*
		 * Try to dequeue one packet.  Stop if the queue is empty.
		 * Use IF_DEQUEUE() here if ALTQ(9) support is unneeded.
		 */
		IFQ_DEQUEUE(&ifp->if_snd, m);
		if (m == NULL)
			break;

		/*
		 * Let bpf(9) at the packet.
		 */
		BPF_MTAP(ifp, m);

		/*
		 * Update the interface counters.
		 */
		if_inc_counter(ifp, IFCOUNTER_OBYTES, m->m_pkthdr.len);
		if_inc_counter(ifp, IFCOUNTER_OPACKETS, 1);

		/*
		 * Finally, just drop the packet.
		 * TODO: Reply to ARP requests unless IFF_NOARP is set.
		 */
		m_freem(m);
	}

	/*
	 * ifp->if_drv_flags &= ~IFF_DRV_OACTIVE;
	 * would be here only if the transmission were synchronous.
	 */
}