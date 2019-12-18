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
struct rdma_addrinfo {int ai_flags; scalar_t__ ai_family; int ai_qp_type; int ai_port_space; int /*<<< orphan*/  ai_dst_canonname; int /*<<< orphan*/  ai_dst_addr; int /*<<< orphan*/  ai_dst_len; int /*<<< orphan*/  ai_src_addr; int /*<<< orphan*/  ai_src_len; } ;
struct addrinfo {scalar_t__ ai_family; int /*<<< orphan*/ * ai_next; int /*<<< orphan*/  ai_canonname; int /*<<< orphan*/  ai_addr; int /*<<< orphan*/  ai_addrlen; void* ai_protocol; int /*<<< orphan*/  ai_socktype; int /*<<< orphan*/  ai_flags; } ;

/* Variables and functions */
 scalar_t__ AF_IB ; 
 int /*<<< orphan*/  AI_NUMERICHOST ; 
 int /*<<< orphan*/  AI_PASSIVE ; 
#define  IBV_QPT_RC 136 
#define  IBV_QPT_UC 135 
#define  IBV_QPT_UD 134 
#define  IBV_QPT_XRC_RECV 133 
#define  IBV_QPT_XRC_SEND 132 
 void* IPPROTO_TCP ; 
 void* IPPROTO_UDP ; 
 int RAI_NUMERICHOST ; 
 int RAI_PASSIVE ; 
#define  RDMA_PS_IB 131 
#define  RDMA_PS_IPOIB 130 
#define  RDMA_PS_TCP 129 
#define  RDMA_PS_UDP 128 
 int /*<<< orphan*/  SOCK_DGRAM ; 
 int /*<<< orphan*/  SOCK_STREAM ; 
 int /*<<< orphan*/  memset (struct addrinfo*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void ucma_convert_to_ai(struct addrinfo *ai,
			       const struct rdma_addrinfo *rai)
{
	memset(ai, 0, sizeof(*ai));
	if (rai->ai_flags & RAI_PASSIVE)
		ai->ai_flags = AI_PASSIVE;
	if (rai->ai_flags & RAI_NUMERICHOST)
		ai->ai_flags |= AI_NUMERICHOST;
	if (rai->ai_family != AF_IB)
		ai->ai_family = rai->ai_family;

	switch (rai->ai_qp_type) {
	case IBV_QPT_RC:
	case IBV_QPT_UC:
	case IBV_QPT_XRC_SEND:
	case IBV_QPT_XRC_RECV:
		ai->ai_socktype = SOCK_STREAM;
		break;
	case IBV_QPT_UD:
		ai->ai_socktype = SOCK_DGRAM;
		break;
	}

	switch (rai->ai_port_space) {
	case RDMA_PS_TCP:
		ai->ai_protocol = IPPROTO_TCP;
		break;
	case RDMA_PS_IPOIB:
	case RDMA_PS_UDP:
		ai->ai_protocol = IPPROTO_UDP;
		break;
	case RDMA_PS_IB:
		if (ai->ai_socktype == SOCK_STREAM)
			ai->ai_protocol = IPPROTO_TCP;
		else if (ai->ai_socktype == SOCK_DGRAM)
			ai->ai_protocol = IPPROTO_UDP;
		break;
	}

	if (rai->ai_flags & RAI_PASSIVE) {
		ai->ai_addrlen = rai->ai_src_len;
		ai->ai_addr = rai->ai_src_addr;
	} else {
		ai->ai_addrlen = rai->ai_dst_len;
		ai->ai_addr = rai->ai_dst_addr;
	}
	ai->ai_canonname = rai->ai_dst_canonname;
	ai->ai_next = NULL;
}