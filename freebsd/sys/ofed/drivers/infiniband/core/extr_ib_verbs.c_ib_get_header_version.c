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
union rdma_network_hdr {int /*<<< orphan*/  ibgrh; int /*<<< orphan*/  roce4grh; } ;
struct ip6_hdr {int ip6_vfc; } ;
struct ip {int ip_v; int ip_hl; scalar_t__ ip_sum; } ;
typedef  int /*<<< orphan*/  ip4h_checked ;

/* Variables and functions */
 int IPV6_VERSION ; 
 int IPV6_VERSION_MASK ; 
 scalar_t__ in_cksum_hdr (struct ip*) ; 
 int /*<<< orphan*/  memcpy (struct ip*,struct ip const*,int) ; 

__attribute__((used)) static int ib_get_header_version(const union rdma_network_hdr *hdr)
{
	const struct ip *ip4h = (const struct ip *)&hdr->roce4grh;
	struct ip ip4h_checked;
	const struct ip6_hdr *ip6h = (const struct ip6_hdr *)&hdr->ibgrh;

	/* If it's IPv6, the version must be 6, otherwise, the first
	 * 20 bytes (before the IPv4 header) are garbled.
	 */
	if ((ip6h->ip6_vfc & IPV6_VERSION_MASK) != IPV6_VERSION)
		return (ip4h->ip_v == 4) ? 4 : 0;
	/* version may be 6 or 4 because the first 20 bytes could be garbled */

	/* RoCE v2 requires no options, thus header length
	 * must be 5 words
	 */
	if (ip4h->ip_hl != 5)
		return 6;

	/* Verify checksum.
	 * We can't write on scattered buffers so we need to copy to
	 * temp buffer.
	 */
	memcpy(&ip4h_checked, ip4h, sizeof(ip4h_checked));
	ip4h_checked.ip_sum = 0;
#if defined(INET) || defined(INET6)
	ip4h_checked.ip_sum = in_cksum_hdr(&ip4h_checked);
#endif
	/* if IPv4 header checksum is OK, believe it */
	if (ip4h->ip_sum == ip4h_checked.ip_sum)
		return 4;
	return 6;
}