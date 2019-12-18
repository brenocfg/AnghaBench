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
typedef  int /*<<< orphan*/  u_char ;
struct pcap_pkthdr {int caplen; } ;
struct l2_packet_data {int /*<<< orphan*/  rx_callback_ctx; int /*<<< orphan*/  (* rx_callback ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned char*,size_t) ;scalar_t__ l2_hdr; } ;
struct l2_ethhdr {int /*<<< orphan*/  h_source; } ;
typedef  int /*<<< orphan*/  pcap_t ;

/* Variables and functions */
 int /*<<< orphan*/ * pcap_next (int /*<<< orphan*/ *,struct pcap_pkthdr*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned char*,size_t) ; 

__attribute__((used)) static void l2_packet_receive(int sock, void *eloop_ctx, void *sock_ctx)
{
	struct l2_packet_data *l2 = eloop_ctx;
	pcap_t *pcap = sock_ctx;
	struct pcap_pkthdr hdr;
	const u_char *packet;
	struct l2_ethhdr *ethhdr;
	unsigned char *buf;
	size_t len;

	packet = pcap_next(pcap, &hdr);

	if (packet == NULL || hdr.caplen < sizeof(*ethhdr))
		return;

	ethhdr = (struct l2_ethhdr *) packet;
	if (l2->l2_hdr) {
		buf = (unsigned char *) ethhdr;
		len = hdr.caplen;
	} else {
		buf = (unsigned char *) (ethhdr + 1);
		len = hdr.caplen - sizeof(*ethhdr);
	}
	l2->rx_callback(l2->rx_callback_ctx, ethhdr->h_source, buf, len);
}