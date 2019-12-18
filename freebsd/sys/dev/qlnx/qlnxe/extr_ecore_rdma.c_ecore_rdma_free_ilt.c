#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct ecore_hwfn {TYPE_1__* p_rdma_info; } ;
struct TYPE_2__ {int /*<<< orphan*/  proto; } ;

/* Variables and functions */
 int /*<<< orphan*/  ECORE_ELEM_CXT ; 
 int /*<<< orphan*/  ECORE_ELEM_SRQ ; 
 int /*<<< orphan*/  ECORE_ELEM_TASK ; 
 int /*<<< orphan*/  OSAL_NULL ; 
 int /*<<< orphan*/  PROTOCOLID_ROCE ; 
 int /*<<< orphan*/  ecore_cxt_free_ilt_range (struct ecore_hwfn*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ecore_cxt_get_proto_cid_count (struct ecore_hwfn*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ecore_cxt_get_proto_cid_start (struct ecore_hwfn*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ecore_cxt_get_proto_tid_count (struct ecore_hwfn*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ecore_cxt_get_srq_count (struct ecore_hwfn*) ; 

__attribute__((used)) static void ecore_rdma_free_ilt(struct ecore_hwfn *p_hwfn)
{
	/* Free Connection CXT */
	ecore_cxt_free_ilt_range(
		p_hwfn, ECORE_ELEM_CXT,
		ecore_cxt_get_proto_cid_start(p_hwfn,
					      p_hwfn->p_rdma_info->proto),
		ecore_cxt_get_proto_cid_count(p_hwfn,
					      p_hwfn->p_rdma_info->proto,
					      OSAL_NULL));

	/* Free Task CXT ( Intentionally RoCE as task-id is shared between
	 * RoCE and iWARP
	 */
	ecore_cxt_free_ilt_range(p_hwfn, ECORE_ELEM_TASK, 0,
				 ecore_cxt_get_proto_tid_count(
					 p_hwfn, PROTOCOLID_ROCE));

	/* Free TSDM CXT */
	ecore_cxt_free_ilt_range(p_hwfn, ECORE_ELEM_SRQ, 0,
				 ecore_cxt_get_srq_count(p_hwfn));
}