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
typedef  int /*<<< orphan*/  uint16_t ;
struct nm_ipv6hdr {int /*<<< orphan*/  nexthdr; } ;

/* Variables and functions */
 int /*<<< orphan*/  in6_cksum_pseudo (void*,size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nm_os_csum_fold (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nm_os_csum_raw (void*,size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nm_prerr (char*) ; 

void
nm_os_csum_tcpudp_ipv6(struct nm_ipv6hdr *ip6h, void *data,
					size_t datalen, uint16_t *check)
{
#ifdef INET6
	*check = in6_cksum_pseudo((void*)ip6h, datalen, ip6h->nexthdr, 0);
	*check = nm_os_csum_fold(nm_os_csum_raw(data, datalen, 0));
#else
	static int notsupported = 0;
	if (!notsupported) {
		notsupported = 1;
		nm_prerr("inet6 segmentation not supported");
	}
#endif
}