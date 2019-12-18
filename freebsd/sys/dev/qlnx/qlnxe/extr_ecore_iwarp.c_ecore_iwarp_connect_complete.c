#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u8 ;
struct ecore_iwarp_ep {scalar_t__ connect_mode; scalar_t__ state; int /*<<< orphan*/  syn; } ;
struct ecore_hwfn {TYPE_2__* p_rdma_info; } ;
struct TYPE_3__ {int /*<<< orphan*/  ll2_syn_handle; } ;
struct TYPE_4__ {TYPE_1__ iwarp; } ;

/* Variables and functions */
 scalar_t__ ECORE_IWARP_EP_ABORTING ; 
 int /*<<< orphan*/  OSAL_NULL ; 
 scalar_t__ RDMA_RETURN_OK ; 
 scalar_t__ TCP_CONNECT_PASSIVE ; 
 int /*<<< orphan*/  ecore_iwarp_ll2_post_rx (struct ecore_hwfn*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ecore_iwarp_mpa_offload (struct ecore_hwfn*,struct ecore_iwarp_ep*) ; 
 int /*<<< orphan*/  ecore_iwarp_mpa_received (struct ecore_hwfn*,struct ecore_iwarp_ep*) ; 
 int /*<<< orphan*/  ecore_iwarp_tcp_connect_unsuccessful (struct ecore_hwfn*,struct ecore_iwarp_ep*,scalar_t__) ; 

__attribute__((used)) static void
ecore_iwarp_connect_complete(struct ecore_hwfn *p_hwfn,
			     struct ecore_iwarp_ep *ep,
			     u8 fw_return_code)
{
	if (ep->connect_mode == TCP_CONNECT_PASSIVE) {
		/* Done with the SYN packet, post back to ll2 rx */
		ecore_iwarp_ll2_post_rx(
			p_hwfn, ep->syn,
			p_hwfn->p_rdma_info->iwarp.ll2_syn_handle);

		ep->syn = OSAL_NULL;

		if (ep->state == ECORE_IWARP_EP_ABORTING)
			return;

		/* If connect failed - upper layer doesn't know about it */
		if (fw_return_code == RDMA_RETURN_OK)
			ecore_iwarp_mpa_received(p_hwfn, ep);
		else
			ecore_iwarp_tcp_connect_unsuccessful(p_hwfn, ep,
							     fw_return_code);

	} else {
		if (fw_return_code == RDMA_RETURN_OK)
			ecore_iwarp_mpa_offload(p_hwfn, ep);
		else
			ecore_iwarp_tcp_connect_unsuccessful(p_hwfn, ep,
							     fw_return_code);
	}
}