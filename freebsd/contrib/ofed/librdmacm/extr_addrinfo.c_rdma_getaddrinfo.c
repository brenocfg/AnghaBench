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
struct rdma_addrinfo {int ai_flags; scalar_t__ ai_src_len; int /*<<< orphan*/  ai_src_addr; scalar_t__ ai_dst_len; int /*<<< orphan*/  ai_dst_addr; int /*<<< orphan*/  ai_port_space; int /*<<< orphan*/  ai_qp_type; int /*<<< orphan*/  ai_family; } ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  ENOMEM ; 
 int ERR (int /*<<< orphan*/ ) ; 
 int RAI_PASSIVE ; 
 struct rdma_addrinfo* calloc (int,int) ; 
 struct rdma_addrinfo nohints ; 
 int /*<<< orphan*/  rdma_freeaddrinfo (struct rdma_addrinfo*) ; 
 int ucma_copy_addr (int /*<<< orphan*/ *,scalar_t__*,int /*<<< orphan*/ ,scalar_t__) ; 
 int ucma_getaddrinfo (char const*,char const*,struct rdma_addrinfo const*,struct rdma_addrinfo*) ; 
 int /*<<< orphan*/  ucma_ib_resolve (struct rdma_addrinfo**,struct rdma_addrinfo const*) ; 
 int ucma_init () ; 

int rdma_getaddrinfo(const char *node, const char *service,
		     const struct rdma_addrinfo *hints,
		     struct rdma_addrinfo **res)
{
	struct rdma_addrinfo *rai;
	int ret;

	if (!service && !node && !hints)
		return ERR(EINVAL);

	ret = ucma_init();
	if (ret)
		return ret;

	rai = calloc(1, sizeof(*rai));
	if (!rai)
		return ERR(ENOMEM);

	if (!hints)
		hints = &nohints;

	if (node || service) {
		ret = ucma_getaddrinfo(node, service, hints, rai);
	} else {
		rai->ai_flags = hints->ai_flags;
		rai->ai_family = hints->ai_family;
		rai->ai_qp_type = hints->ai_qp_type;
		rai->ai_port_space = hints->ai_port_space;
		if (hints->ai_dst_len) {
			ret = ucma_copy_addr(&rai->ai_dst_addr, &rai->ai_dst_len,
					     hints->ai_dst_addr, hints->ai_dst_len);
		}
	}
	if (ret)
		goto err;

	if (!rai->ai_src_len && hints->ai_src_len) {
		ret = ucma_copy_addr(&rai->ai_src_addr, &rai->ai_src_len,
				     hints->ai_src_addr, hints->ai_src_len);
		if (ret)
			goto err;
	}

	if (!(rai->ai_flags & RAI_PASSIVE))
		ucma_ib_resolve(&rai, hints);

	*res = rai;
	return 0;

err:
	rdma_freeaddrinfo(rai);
	return ret;
}