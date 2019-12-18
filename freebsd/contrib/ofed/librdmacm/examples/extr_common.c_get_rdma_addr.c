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
struct rdma_addrinfo {int ai_flags; int /*<<< orphan*/  ai_src_len; int /*<<< orphan*/  ai_src_addr; } ;

/* Variables and functions */
 int RAI_PASSIVE ; 
 int /*<<< orphan*/  rdma_freeaddrinfo (struct rdma_addrinfo*) ; 
 int rdma_getaddrinfo (char const*,char const*,struct rdma_addrinfo*,struct rdma_addrinfo**) ; 

int get_rdma_addr(const char *src, const char *dst, const char *port,
		  struct rdma_addrinfo *hints, struct rdma_addrinfo **rai)
{
	struct rdma_addrinfo rai_hints, *res;
	int ret;

	if (hints->ai_flags & RAI_PASSIVE)
		return rdma_getaddrinfo(src, port, hints, rai);

	rai_hints = *hints;
	if (src) {
		rai_hints.ai_flags |= RAI_PASSIVE;
		ret = rdma_getaddrinfo(src, NULL, &rai_hints, &res);
		if (ret)
			return ret;

		rai_hints.ai_src_addr = res->ai_src_addr;
		rai_hints.ai_src_len = res->ai_src_len;
		rai_hints.ai_flags &= ~RAI_PASSIVE;
	}

	ret = rdma_getaddrinfo(dst, port, &rai_hints, rai);
	if (src)
		rdma_freeaddrinfo(res);

	return ret;
}