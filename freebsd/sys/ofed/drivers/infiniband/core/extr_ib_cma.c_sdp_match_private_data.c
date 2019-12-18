#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct in6_addr {int dummy; } ;
struct sockaddr_in6 {struct in6_addr sin6_addr; } ;
struct TYPE_6__ {int /*<<< orphan*/  s_addr; } ;
struct sockaddr_in {TYPE_3__ sin_addr; } ;
struct sockaddr {int sa_family; } ;
struct TYPE_4__ {int /*<<< orphan*/  addr; } ;
struct TYPE_5__ {int /*<<< orphan*/  ip6; TYPE_1__ ip4; } ;
struct sdp_hh {TYPE_2__ dst_addr; } ;
struct rdma_id_private {int dummy; } ;
typedef  int /*<<< orphan*/  ip6_addr ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
#define  AF_IB 130 
#define  AF_INET 129 
#define  AF_INET6 128 
 int /*<<< orphan*/  cma_any_addr (struct sockaddr*) ; 
 int /*<<< orphan*/  cma_ip6_clear_scope_id (struct in6_addr*) ; 
 int /*<<< orphan*/  memcmp (int /*<<< orphan*/ *,struct in6_addr*,int) ; 
 int sdp_get_ip_ver (struct sdp_hh const*) ; 

__attribute__((used)) static bool sdp_match_private_data(struct rdma_id_private *id_priv,
				   const struct sdp_hh *hdr,
				   struct sockaddr *addr)
{
	__be32 ip4_addr;
	struct in6_addr ip6_addr;

	switch (addr->sa_family) {
	case AF_INET:
		ip4_addr = ((struct sockaddr_in *)addr)->sin_addr.s_addr;
		if (sdp_get_ip_ver(hdr) != 4)
			return false;
		if (!cma_any_addr(addr) &&
		    hdr->dst_addr.ip4.addr != ip4_addr)
			return false;
		break;
	case AF_INET6:
		ip6_addr = ((struct sockaddr_in6 *)addr)->sin6_addr;
		if (sdp_get_ip_ver(hdr) != 6)
			return false;
		cma_ip6_clear_scope_id(&ip6_addr);
		if (!cma_any_addr(addr) &&
		    memcmp(&hdr->dst_addr.ip6, &ip6_addr, sizeof(ip6_addr)))
			return false;
		break;
	case AF_IB:
		return true;
	default:
		return false;
	}

	return true;
}