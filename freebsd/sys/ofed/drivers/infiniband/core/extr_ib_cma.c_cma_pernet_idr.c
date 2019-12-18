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
struct vnet {int dummy; } ;
struct idr {int dummy; } ;
struct cma_pernet {struct idr sdp_ps; struct idr ib_ps; struct idr ipoib_ps; struct idr udp_ps; struct idr tcp_ps; } ;
typedef  enum rdma_port_space { ____Placeholder_rdma_port_space } rdma_port_space ;

/* Variables and functions */
#define  RDMA_PS_IB 132 
#define  RDMA_PS_IPOIB 131 
#define  RDMA_PS_SDP 130 
#define  RDMA_PS_TCP 129 
#define  RDMA_PS_UDP 128 
 struct cma_pernet* cma_pernet_ptr (struct vnet*) ; 

__attribute__((used)) static struct idr *cma_pernet_idr(struct vnet *net, enum rdma_port_space ps)
{
	struct cma_pernet *pernet = cma_pernet_ptr(net);

	switch (ps) {
	case RDMA_PS_TCP:
		return &pernet->tcp_ps;
	case RDMA_PS_UDP:
		return &pernet->udp_ps;
	case RDMA_PS_IPOIB:
		return &pernet->ipoib_ps;
	case RDMA_PS_IB:
		return &pernet->ib_ps;
	case RDMA_PS_SDP:
		return &pernet->sdp_ps;
	default:
		return NULL;
	}
}