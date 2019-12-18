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
typedef  scalar_t__ uint16_t ;
typedef  scalar_t__ u_int ;
typedef  int /*<<< orphan*/  u_char ;
struct sll_header {int /*<<< orphan*/  sll_protocol; } ;
struct pcap_pkthdr {scalar_t__ caplen; scalar_t__ len; } ;
struct TYPE_2__ {int /*<<< orphan*/  can_id; } ;
typedef  TYPE_1__ pcap_can_socketcan_hdr ;

/* Variables and functions */
 scalar_t__ EXTRACT_16BITS (int /*<<< orphan*/ *) ; 
 scalar_t__ LINUX_SLL_P_CAN ; 
 scalar_t__ LINUX_SLL_P_CANFD ; 
 int /*<<< orphan*/  SWAPLONG (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
swap_linux_sll_header(const struct pcap_pkthdr *hdr, u_char *buf)
{
	u_int caplen = hdr->caplen;
	u_int length = hdr->len;
	struct sll_header *shdr = (struct sll_header *)buf;
	uint16_t protocol;
	pcap_can_socketcan_hdr *chdr;

	if (caplen < (u_int) sizeof(struct sll_header) ||
	    length < (u_int) sizeof(struct sll_header)) {
		/* Not enough data to have the protocol field */
		return;
	}

	protocol = EXTRACT_16BITS(&shdr->sll_protocol);
	if (protocol != LINUX_SLL_P_CAN && protocol != LINUX_SLL_P_CANFD)
		return;

	/*
	 * SocketCAN packet; fix up the packet's header.
	 */
	chdr = (pcap_can_socketcan_hdr *)(buf + sizeof(struct sll_header));
	if (caplen < (u_int) sizeof(struct sll_header) + sizeof(chdr->can_id) ||
	    length < (u_int) sizeof(struct sll_header) + sizeof(chdr->can_id)) {
		/* Not enough data to have the CAN ID */
		return;
	}
	chdr->can_id = SWAPLONG(chdr->can_id);
}