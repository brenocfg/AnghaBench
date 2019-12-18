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
typedef  int /*<<< orphan*/  u16 ;
struct ib_pd {int dummy; } ;
struct qlnxr_pd {struct ib_pd ibpd; TYPE_1__* uctx; int /*<<< orphan*/  pd_id; } ;
struct qlnxr_dev {int /*<<< orphan*/  pd_count; int /*<<< orphan*/ * rdma_ctx; int /*<<< orphan*/ * ha; } ;
struct ib_udata {int dummy; } ;
struct ib_ucontext {int dummy; } ;
struct ib_device {int dummy; } ;
typedef  int /*<<< orphan*/  qlnx_host_t ;
struct TYPE_2__ {struct qlnxr_pd* pd; } ;

/* Variables and functions */
 int ENOMEM ; 
 struct ib_pd* ERR_PTR (int) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  QL_DPRINT11 (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  QL_DPRINT12 (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  atomic_add_rel_32 (int /*<<< orphan*/ *,int) ; 
 int ecore_rdma_alloc_pd (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ecore_rdma_free_pd (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct qlnxr_dev* get_qlnxr_dev (struct ib_device*) ; 
 TYPE_1__* get_qlnxr_ucontext (struct ib_ucontext*) ; 
 int ib_copy_to_udata (struct ib_udata*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  kfree (struct qlnxr_pd*) ; 
 struct qlnxr_pd* kzalloc (int,int /*<<< orphan*/ ) ; 

struct ib_pd *
qlnxr_alloc_pd(struct ib_device *ibdev, struct ib_ucontext *context,
	struct ib_udata *udata)
{
	struct qlnxr_pd		*pd = NULL;
	u16			pd_id;
	int			rc;
	struct qlnxr_dev	*dev;
	qlnx_host_t		*ha;

	dev = get_qlnxr_dev(ibdev);
	ha = dev->ha;

	QL_DPRINT12(ha, "ibdev = %p context = %p"
		" udata = %p enter\n", ibdev, context, udata);

	if (dev->rdma_ctx == NULL) {
		QL_DPRINT11(ha, "dev->rdma_ctx = NULL\n");
		rc = -1;
		goto err;
	}

	pd = kzalloc(sizeof(*pd), GFP_KERNEL);
	if (!pd) {
		rc = -ENOMEM;
		QL_DPRINT11(ha, "kzalloc(pd) = NULL\n");
		goto err;
	}

	rc = ecore_rdma_alloc_pd(dev->rdma_ctx, &pd_id);
	if (rc)	{
		QL_DPRINT11(ha, "ecore_rdma_alloc_pd failed\n");
		goto err;
	}

	pd->pd_id = pd_id;

	if (udata && context) {

		rc = ib_copy_to_udata(udata, &pd->pd_id, sizeof(pd->pd_id));
		if (rc) {
			QL_DPRINT11(ha, "ib_copy_to_udata failed\n");
			ecore_rdma_free_pd(dev->rdma_ctx, pd_id);
			goto err;
		}

		pd->uctx = get_qlnxr_ucontext(context);
		pd->uctx->pd = pd;
	}

	atomic_add_rel_32(&dev->pd_count, 1);
	QL_DPRINT12(ha, "exit [pd, pd_id, pd_count] = [%p, 0x%x, %d]\n",
		pd, pd_id, dev->pd_count);

	return &pd->ibpd;

err:
	kfree(pd);
	QL_DPRINT12(ha, "exit -1\n");
	return ERR_PTR(rc);
}