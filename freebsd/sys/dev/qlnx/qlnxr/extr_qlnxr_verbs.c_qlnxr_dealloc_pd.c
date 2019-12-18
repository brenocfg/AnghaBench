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
struct qlnxr_pd {int /*<<< orphan*/  pd_id; } ;
struct qlnxr_dev {int /*<<< orphan*/  pd_count; int /*<<< orphan*/  rdma_ctx; int /*<<< orphan*/ * ha; } ;
struct ib_pd {int /*<<< orphan*/  device; } ;
typedef  int /*<<< orphan*/  qlnx_host_t ;

/* Variables and functions */
 int /*<<< orphan*/  QL_DPRINT11 (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  QL_DPRINT12 (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  atomic_subtract_rel_32 (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  ecore_rdma_free_pd (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct qlnxr_dev* get_qlnxr_dev (int /*<<< orphan*/ ) ; 
 struct qlnxr_pd* get_qlnxr_pd (struct ib_pd*) ; 
 int /*<<< orphan*/  kfree (struct qlnxr_pd*) ; 

int
qlnxr_dealloc_pd(struct ib_pd *ibpd)
{
	struct qlnxr_pd		*pd;
	struct qlnxr_dev	*dev;
	qlnx_host_t		*ha;

	pd = get_qlnxr_pd(ibpd);
	dev = get_qlnxr_dev((ibpd->device));
	ha = dev->ha;

	QL_DPRINT12(ha, "enter\n");

	if (pd == NULL) {
		QL_DPRINT11(ha, "pd = NULL\n");
	} else {
		ecore_rdma_free_pd(dev->rdma_ctx, pd->pd_id);
		kfree(pd);
		atomic_subtract_rel_32(&dev->pd_count, 1);
		QL_DPRINT12(ha, "exit [pd, pd_id, pd_count] = [%p, 0x%x, %d]\n",
			pd, pd->pd_id, dev->pd_count);
	}

	QL_DPRINT12(ha, "exit\n");
	return 0;
}