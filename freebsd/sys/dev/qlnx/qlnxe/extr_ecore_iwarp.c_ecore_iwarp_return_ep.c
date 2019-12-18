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
struct ecore_iwarp_ep {scalar_t__ tcp_cid; int /*<<< orphan*/  cm_info; TYPE_3__* qp; int /*<<< orphan*/  state; } ;
struct ecore_hwfn {TYPE_2__* p_rdma_info; } ;
struct TYPE_6__ {void* ep; } ;
struct TYPE_4__ {int /*<<< orphan*/  ep_free_list; } ;
struct TYPE_5__ {TYPE_1__ iwarp; } ;

/* Variables and functions */
 int /*<<< orphan*/  ECORE_IWARP_EP_INIT ; 
 scalar_t__ ECORE_IWARP_INVALID_TCP_CID ; 
 int /*<<< orphan*/  OSAL_MEMSET (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 void* OSAL_NULL ; 
 int /*<<< orphan*/  ecore_iwarp_alloc_tcp_cid (struct ecore_hwfn*,scalar_t__*) ; 
 int /*<<< orphan*/  ecore_iwarp_move_to_ep_list (struct ecore_hwfn*,int /*<<< orphan*/ *,struct ecore_iwarp_ep*) ; 

__attribute__((used)) static void
ecore_iwarp_return_ep(struct ecore_hwfn *p_hwfn,
		      struct ecore_iwarp_ep *ep)
{
	ep->state = ECORE_IWARP_EP_INIT;
	if (ep->qp)
		ep->qp->ep = OSAL_NULL;
	ep->qp = OSAL_NULL;
	OSAL_MEMSET(&ep->cm_info, 0, sizeof(ep->cm_info));

	if (ep->tcp_cid == ECORE_IWARP_INVALID_TCP_CID) {
		/* We don't care about the return code, it's ok if tcp_cid
		 * remains invalid...in this case we'll defer allocation
		 */
		ecore_iwarp_alloc_tcp_cid(p_hwfn, &ep->tcp_cid);
	}

	ecore_iwarp_move_to_ep_list(p_hwfn,
				    &p_hwfn->p_rdma_info->iwarp.ep_free_list,
				    ep);
}