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
typedef  int /*<<< orphan*/  const u8 ;
typedef  int /*<<< orphan*/  u16 ;
struct l2_packet_data {int /*<<< orphan*/  pcap; int /*<<< orphan*/  const* own_addr; int /*<<< orphan*/  l2_hdr; } ;
struct l2_ethhdr {int /*<<< orphan*/  h_proto; struct l2_ethhdr* h_source; struct l2_ethhdr* h_dest; } ;

/* Variables and functions */
 size_t ETH_ALEN ; 
 int /*<<< orphan*/  htons (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  os_free (struct l2_ethhdr*) ; 
 struct l2_ethhdr* os_malloc (int) ; 
 int /*<<< orphan*/  os_memcpy (struct l2_ethhdr*,int /*<<< orphan*/  const*,size_t) ; 
 int pcap_inject (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,size_t) ; 

int l2_packet_send(struct l2_packet_data *l2, const u8 *dst_addr, u16 proto,
		   const u8 *buf, size_t len)
{
	if (!l2->l2_hdr) {
		int ret;
		struct l2_ethhdr *eth = os_malloc(sizeof(*eth) + len);
		if (eth == NULL)
			return -1;
		os_memcpy(eth->h_dest, dst_addr, ETH_ALEN);
		os_memcpy(eth->h_source, l2->own_addr, ETH_ALEN);
		eth->h_proto = htons(proto);
		os_memcpy(eth + 1, buf, len);
		ret = pcap_inject(l2->pcap, (u8 *) eth, len + sizeof(*eth));
		os_free(eth);
		return ret;
	} else
		return pcap_inject(l2->pcap, buf, len);
}