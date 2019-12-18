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
struct nptv6_cfg {int dummy; } ;
struct mbuf {int m_len; } ;
struct ip6_hdr {int ip6_nxt; } ;
struct ip6_hbh {int ip6h_nxt; int ip6h_len; } ;

/* Variables and functions */
 int IPPROTO_DSTOPTS ; 
 int IPPROTO_HOPOPTS ; 
 int IPPROTO_ROUTING ; 
 void* mtodo (struct mbuf*,int) ; 

__attribute__((used)) static int
nptv6_getlasthdr(struct nptv6_cfg *cfg, struct mbuf *m, int *offset)
{
	struct ip6_hdr *ip6;
	struct ip6_hbh *hbh;
	int proto, hlen;

	hlen = (offset == NULL) ? 0: *offset;
	if (m->m_len < hlen)
		return (-1);
	ip6 = mtodo(m, hlen);
	hlen += sizeof(*ip6);
	proto = ip6->ip6_nxt;
	while (proto == IPPROTO_HOPOPTS || proto == IPPROTO_ROUTING ||
	    proto == IPPROTO_DSTOPTS) {
		hbh = mtodo(m, hlen);
		if (m->m_len < hlen)
			return (-1);
		proto = hbh->ip6h_nxt;
		hlen += (hbh->ip6h_len + 1) << 3;
	}
	if (offset != NULL)
		*offset = hlen;
	return (proto);
}