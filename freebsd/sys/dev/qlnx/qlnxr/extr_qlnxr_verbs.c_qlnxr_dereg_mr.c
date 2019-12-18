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
struct TYPE_2__ {int /*<<< orphan*/  pbl_table; int /*<<< orphan*/  pbl_info; } ;
struct qlnxr_mr {scalar_t__ type; struct qlnxr_mr* pages; scalar_t__ umem; TYPE_1__ info; } ;
struct qlnxr_dev {int /*<<< orphan*/ * ha; } ;
struct ib_mr {int /*<<< orphan*/  device; } ;
typedef  int /*<<< orphan*/  qlnx_host_t ;

/* Variables and functions */
 scalar_t__ QLNXR_MR_DMA ; 
 scalar_t__ QLNXR_MR_FRMR ; 
 int /*<<< orphan*/  QL_DPRINT12 (int /*<<< orphan*/ *,char*) ; 
 struct qlnxr_dev* get_qlnxr_dev (int /*<<< orphan*/ ) ; 
 struct qlnxr_mr* get_qlnxr_mr (struct ib_mr*) ; 
 int /*<<< orphan*/  ib_umem_release (scalar_t__) ; 
 int /*<<< orphan*/  kfree (struct qlnxr_mr*) ; 
 int /*<<< orphan*/  qlnxr_free_pbl (struct qlnxr_dev*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int
qlnxr_dereg_mr(struct ib_mr *ib_mr)
{
	struct qlnxr_mr	*mr = get_qlnxr_mr(ib_mr);
	struct qlnxr_dev *dev = get_qlnxr_dev((ib_mr->device));
	int		rc = 0;
	qlnx_host_t	*ha;

	ha = dev->ha;

	QL_DPRINT12(ha, "enter\n");

	if ((mr->type != QLNXR_MR_DMA) && (mr->type != QLNXR_MR_FRMR))
		qlnxr_free_pbl(dev, &mr->info.pbl_info, mr->info.pbl_table);

	/* it could be user registered memory. */
	if (mr->umem)
		ib_umem_release(mr->umem);

	kfree(mr->pages);

	kfree(mr);

	QL_DPRINT12(ha, "exit\n");
	return rc;
}