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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  void* uint16_t ;
typedef  int u_int ;
struct nm_udphdr {void* check; void* len; } ;
struct nm_tcphdr {int flags; void* check; int /*<<< orphan*/  seq; } ;
struct nm_ipv6hdr {void* payload_len; } ;
struct nm_iphdr {void* check; void* id; void* tot_len; } ;
struct TYPE_2__ {void* tot_len; } ;

/* Variables and functions */
 int be16toh (void*) ; 
 int be32toh (int /*<<< orphan*/ ) ; 
 void* htobe16 (int) ; 
 int /*<<< orphan*/  htobe32 (int) ; 
 TYPE_1__* ip ; 
 void* nm_os_csum_ipv4 (struct nm_iphdr*) ; 
 int /*<<< orphan*/  nm_os_csum_tcpudp_ipv4 (struct nm_iphdr*,int /*<<< orphan*/ *,int,void**) ; 
 int /*<<< orphan*/  nm_os_csum_tcpudp_ipv6 (struct nm_ipv6hdr*,int /*<<< orphan*/ *,int,void**) ; 
 int /*<<< orphan*/  nm_prdis (char*,int) ; 

__attribute__((used)) static void
gso_fix_segment(uint8_t *pkt, size_t len, u_int ipv4, u_int iphlen, u_int tcp,
		u_int idx, u_int segmented_bytes, u_int last_segment)
{
	struct nm_iphdr *iph = (struct nm_iphdr *)(pkt);
	struct nm_ipv6hdr *ip6h = (struct nm_ipv6hdr *)(pkt);
	uint16_t *check = NULL;
	uint8_t *check_data = NULL;

	if (ipv4) {
		/* Set the IPv4 "Total Length" field. */
		iph->tot_len = htobe16(len);
		nm_prdis("ip total length %u", be16toh(ip->tot_len));

		/* Set the IPv4 "Identification" field. */
		iph->id = htobe16(be16toh(iph->id) + idx);
		nm_prdis("ip identification %u", be16toh(iph->id));

		/* Compute and insert the IPv4 header checksum. */
		iph->check = 0;
		iph->check = nm_os_csum_ipv4(iph);
		nm_prdis("IP csum %x", be16toh(iph->check));
	} else {
		/* Set the IPv6 "Payload Len" field. */
		ip6h->payload_len = htobe16(len-iphlen);
	}

	if (tcp) {
		struct nm_tcphdr *tcph = (struct nm_tcphdr *)(pkt + iphlen);

		/* Set the TCP sequence number. */
		tcph->seq = htobe32(be32toh(tcph->seq) + segmented_bytes);
		nm_prdis("tcp seq %u", be32toh(tcph->seq));

		/* Zero the PSH and FIN TCP flags if this is not the last
		   segment. */
		if (!last_segment)
			tcph->flags &= ~(0x8 | 0x1);
		nm_prdis("last_segment %u", last_segment);

		check = &tcph->check;
		check_data = (uint8_t *)tcph;
	} else { /* UDP */
		struct nm_udphdr *udph = (struct nm_udphdr *)(pkt + iphlen);

		/* Set the UDP 'Length' field. */
		udph->len = htobe16(len-iphlen);

		check = &udph->check;
		check_data = (uint8_t *)udph;
	}

	/* Compute and insert TCP/UDP checksum. */
	*check = 0;
	if (ipv4)
		nm_os_csum_tcpudp_ipv4(iph, check_data, len-iphlen, check);
	else
		nm_os_csum_tcpudp_ipv6(ip6h, check_data, len-iphlen, check);

	nm_prdis("TCP/UDP csum %x", be16toh(*check));
}