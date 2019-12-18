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
struct sockaddr_ll {scalar_t__ sll_pkttype; scalar_t__ sll_ifindex; scalar_t__ sll_protocol; } ;
struct pcap_linux {scalar_t__ lo_ifindex; } ;
struct TYPE_3__ {scalar_t__ direction; struct pcap_linux* priv; } ;
typedef  TYPE_1__ pcap_t ;

/* Variables and functions */
 scalar_t__ LINUX_SLL_P_CAN ; 
 scalar_t__ LINUX_SLL_P_CANFD ; 
 scalar_t__ PACKET_OUTGOING ; 
 scalar_t__ PCAP_D_IN ; 
 scalar_t__ PCAP_D_OUT ; 

__attribute__((used)) static inline int
linux_check_direction(const pcap_t *handle, const struct sockaddr_ll *sll)
{
	struct pcap_linux	*handlep = handle->priv;

	if (sll->sll_pkttype == PACKET_OUTGOING) {
		/*
		 * Outgoing packet.
		 * If this is from the loopback device, reject it;
		 * we'll see the packet as an incoming packet as well,
		 * and we don't want to see it twice.
		 */
		if (sll->sll_ifindex == handlep->lo_ifindex)
			return 0;

		/*
		 * If this is an outgoing CAN or CAN FD frame, and
		 * the user doesn't only want outgoing packets,
		 * reject it; CAN devices and drivers, and the CAN
		 * stack, always arrange to loop back transmitted
		 * packets, so they also appear as incoming packets.
		 * We don't want duplicate packets, and we can't
		 * easily distinguish packets looped back by the CAN
		 * layer than those received by the CAN layer, so we
		 * eliminate this packet instead.
		 */
		if ((sll->sll_protocol == LINUX_SLL_P_CAN ||
		     sll->sll_protocol == LINUX_SLL_P_CANFD) &&
		     handle->direction != PCAP_D_OUT)
			return 0;

		/*
		 * If the user only wants incoming packets, reject it.
		 */
		if (handle->direction == PCAP_D_IN)
			return 0;
	} else {
		/*
		 * Incoming packet.
		 * If the user only wants outgoing packets, reject it.
		 */
		if (handle->direction == PCAP_D_OUT)
			return 0;
	}
	return 1;
}