#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct qlnxr_dev {TYPE_3__* ha; int /*<<< orphan*/  rdma_ctx; } ;
struct TYPE_6__ {int /*<<< orphan*/  umem; int /*<<< orphan*/  pbl_tbl; int /*<<< orphan*/  pbl_info; } ;
struct qlnxr_cq {int destroyed; scalar_t__ cq_type; int /*<<< orphan*/  icid; int /*<<< orphan*/  sig; TYPE_2__ q; int /*<<< orphan*/  pbl; } ;
struct ib_cq {TYPE_1__* uobject; int /*<<< orphan*/  device; } ;
struct ecore_rdma_destroy_cq_out_params {int dummy; } ;
struct ecore_rdma_destroy_cq_in_params {int /*<<< orphan*/  icid; } ;
struct TYPE_7__ {int /*<<< orphan*/  cdev; } ;
typedef  TYPE_3__ qlnx_host_t ;
struct TYPE_5__ {scalar_t__ context; } ;

/* Variables and functions */
 scalar_t__ QLNXR_CQ_TYPE_GSI ; 
 int /*<<< orphan*/  QL_DPRINT12 (TYPE_3__*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ecore_chain_free (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int ecore_rdma_destroy_cq (int /*<<< orphan*/ ,struct ecore_rdma_destroy_cq_in_params*,struct ecore_rdma_destroy_cq_out_params*) ; 
 struct qlnxr_cq* get_qlnxr_cq (struct ib_cq*) ; 
 struct qlnxr_dev* get_qlnxr_dev (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ib_umem_release (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct qlnxr_cq*) ; 
 int /*<<< orphan*/  qlnxr_free_pbl (struct qlnxr_dev*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int
qlnxr_destroy_cq(struct ib_cq *ibcq)
{
	struct qlnxr_dev			*dev = get_qlnxr_dev((ibcq->device));
	struct ecore_rdma_destroy_cq_out_params oparams;
	struct ecore_rdma_destroy_cq_in_params	iparams;
	struct qlnxr_cq				*cq = get_qlnxr_cq(ibcq);
	int					rc = 0;
	qlnx_host_t				*ha;

	ha = dev->ha;

	QL_DPRINT12(ha, "enter cq_id = %d\n", cq->icid);

	cq->destroyed = 1;

	/* TODO: Syncronize irq of the CNQ the CQ belongs to for validation
	 * that all completions with notification are dealt with. The rest
	 * of the completions are not interesting
	 */

	/* GSIs CQs are handled by driver, so they don't exist in the FW */

	if (cq->cq_type != QLNXR_CQ_TYPE_GSI) {

		iparams.icid = cq->icid;

		rc = ecore_rdma_destroy_cq(dev->rdma_ctx, &iparams, &oparams);

		if (rc) {
			QL_DPRINT12(ha, "ecore_rdma_destroy_cq failed cq_id = %d\n",
				cq->icid);
			return rc;
		}

		QL_DPRINT12(ha, "free cq->pbl cq_id = %d\n", cq->icid);
		ecore_chain_free(&dev->ha->cdev, &cq->pbl);
	}

	if (ibcq->uobject && ibcq->uobject->context) {
		qlnxr_free_pbl(dev, &cq->q.pbl_info, cq->q.pbl_tbl);
		ib_umem_release(cq->q.umem);
	}

	cq->sig = ~cq->sig;

	kfree(cq);

	QL_DPRINT12(ha, "exit cq_id = %d\n", cq->icid);

	return rc;
}