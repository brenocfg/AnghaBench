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
struct nptv6_cfg {int flags; } ;
struct in6_addr {int* s6_addr16; scalar_t__* s6_addr32; } ;

/* Variables and functions */
 int NPTV6_48PLEN ; 

__attribute__((used)) static int
nptv6_search_index(struct nptv6_cfg *cfg, struct in6_addr *a)
{
	int idx;

	if (cfg->flags & NPTV6_48PLEN)
		return (3);

	/* Search suitable word index for adjustment */
	for (idx = 4; idx < 8; idx++)
		if (a->s6_addr16[idx] != 0xffff)
			break;
	/*
	 * RFC 6296 p3.7: If an NPTv6 Translator discovers a datagram with
	 * an IID of all-zeros while performing address mapping, that
	 * datagram MUST be dropped, and an ICMPv6 Parameter Problem error
	 * SHOULD be generated.
	 */
	if (idx == 8 ||
	    (a->s6_addr32[2] == 0 && a->s6_addr32[3] == 0))
		return (-1);
	return (idx);
}