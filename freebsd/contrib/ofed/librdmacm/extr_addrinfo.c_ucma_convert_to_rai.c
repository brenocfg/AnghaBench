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
struct sockaddr_in6 {int dummy; } ;
struct sockaddr_ib {int dummy; } ;
struct rdma_addrinfo {int ai_flags; scalar_t__ ai_family; int /*<<< orphan*/  ai_dst_len; int /*<<< orphan*/  ai_dst_addr; scalar_t__ ai_port_space; void* ai_dst_canonname; int /*<<< orphan*/  ai_src_len; int /*<<< orphan*/  ai_src_addr; void* ai_src_canonname; scalar_t__ ai_qp_type; } ;
struct addrinfo {int ai_socktype; int ai_protocol; int ai_flags; scalar_t__ ai_family; int /*<<< orphan*/  ai_addrlen; scalar_t__ ai_addr; scalar_t__ ai_canonname; } ;

/* Variables and functions */
 scalar_t__ AF_IB ; 
 int AI_PASSIVE ; 
 scalar_t__ IBV_QPT_RC ; 
 scalar_t__ IBV_QPT_UD ; 
#define  IPPROTO_TCP 131 
#define  IPPROTO_UDP 130 
 int RAI_FAMILY ; 
 int RAI_NUMERICHOST ; 
 int RAI_PASSIVE ; 
 scalar_t__ RDMA_PS_TCP ; 
 scalar_t__ RDMA_PS_UDP ; 
#define  SOCK_DGRAM 129 
#define  SOCK_STREAM 128 
 void* strdup (scalar_t__) ; 
 int ucma_convert_in6 (scalar_t__,struct sockaddr_ib**,int /*<<< orphan*/ *,struct sockaddr_in6*,int /*<<< orphan*/ ) ; 
 int ucma_copy_addr (int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ucma_convert_to_rai(struct rdma_addrinfo *rai,
			       const struct rdma_addrinfo *hints,
			       const struct addrinfo *ai)
{
	int ret;

	if (hints->ai_qp_type) {
		rai->ai_qp_type = hints->ai_qp_type;
	} else {
		switch (ai->ai_socktype) {
		case SOCK_STREAM:
			rai->ai_qp_type = IBV_QPT_RC;
			break;
		case SOCK_DGRAM:
			rai->ai_qp_type = IBV_QPT_UD;
			break;
		}
	}

	if (hints->ai_port_space) {
		rai->ai_port_space = hints->ai_port_space;
	} else {
		switch (ai->ai_protocol) {
		case IPPROTO_TCP:
			rai->ai_port_space = RDMA_PS_TCP;
			break;
		case IPPROTO_UDP:
			rai->ai_port_space = RDMA_PS_UDP;
			break;
		}
	}

	if (ai->ai_flags & AI_PASSIVE) {
		rai->ai_flags = RAI_PASSIVE;
		if (ai->ai_canonname)
			rai->ai_src_canonname = strdup(ai->ai_canonname);

		if ((hints->ai_flags & RAI_FAMILY) && (hints->ai_family == AF_IB) &&
		    (hints->ai_flags & RAI_NUMERICHOST)) {
			rai->ai_family = AF_IB;
			ret = ucma_convert_in6(rai->ai_port_space,
					       (struct sockaddr_ib **) &rai->ai_src_addr,
					       &rai->ai_src_len,
					       (struct sockaddr_in6 *) ai->ai_addr,
					       ai->ai_addrlen);
		} else {
			rai->ai_family = ai->ai_family;
			ret = ucma_copy_addr(&rai->ai_src_addr, &rai->ai_src_len,
					     ai->ai_addr, ai->ai_addrlen);
		}
	} else {
		if (ai->ai_canonname)
			rai->ai_dst_canonname = strdup(ai->ai_canonname);

		if ((hints->ai_flags & RAI_FAMILY) && (hints->ai_family == AF_IB) &&
		    (hints->ai_flags & RAI_NUMERICHOST)) {
			rai->ai_family = AF_IB;
			ret = ucma_convert_in6(rai->ai_port_space,
					       (struct sockaddr_ib **) &rai->ai_dst_addr,
					       &rai->ai_dst_len,
					       (struct sockaddr_in6 *) ai->ai_addr,
					       ai->ai_addrlen);
		} else {
			rai->ai_family = ai->ai_family;
			ret = ucma_copy_addr(&rai->ai_dst_addr, &rai->ai_dst_len,
					     ai->ai_addr, ai->ai_addrlen);
		}
	}
	return ret;
}