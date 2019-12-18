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
struct qlnxr_pbl {int /*<<< orphan*/  pa; int /*<<< orphan*/  list_entry; } ;
struct qlnxr_dev {int /*<<< orphan*/ * ha; } ;
struct mr_info {int /*<<< orphan*/  free_pbl_list; int /*<<< orphan*/  pbl_info; TYPE_1__* pbl_table; int /*<<< orphan*/  inuse_pbl_list; } ;
typedef  int /*<<< orphan*/  qlnx_host_t ;
struct TYPE_2__ {int /*<<< orphan*/  pa; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  QL_DPRINT11 (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  QL_DPRINT12 (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  free_mr_info (struct qlnxr_dev*,struct mr_info*) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 void* qlnxr_alloc_pbl_tbl (struct qlnxr_dev*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int qlnxr_prepare_pbl_tbl (struct qlnxr_dev*,int /*<<< orphan*/ *,size_t,int) ; 

__attribute__((used)) static int
qlnxr_init_mr_info(struct qlnxr_dev *dev, struct mr_info *info,
	size_t page_list_len, bool two_layered)
{
	int			rc;
	struct qlnxr_pbl	*tmp;
	qlnx_host_t		*ha;

	ha = dev->ha;

	QL_DPRINT12(ha, "enter\n");

	INIT_LIST_HEAD(&info->free_pbl_list);
	INIT_LIST_HEAD(&info->inuse_pbl_list);

	rc = qlnxr_prepare_pbl_tbl(dev, &info->pbl_info,
				  page_list_len, two_layered);
	if (rc) {
		QL_DPRINT11(ha, "qlnxr_prepare_pbl_tbl [%d]\n", rc);
		goto done;
	}

	info->pbl_table = qlnxr_alloc_pbl_tbl(dev, &info->pbl_info, GFP_KERNEL);

	if (!info->pbl_table) {
		rc = -ENOMEM;
		QL_DPRINT11(ha, "qlnxr_alloc_pbl_tbl returned NULL\n");
		goto done;
	}

	QL_DPRINT12(ha, "pbl_table_pa = %pa\n", &info->pbl_table->pa);

	/* in usual case we use 2 PBLs, so we add one to free
	 * list and allocating another one
	 */
	tmp = qlnxr_alloc_pbl_tbl(dev, &info->pbl_info, GFP_KERNEL);

	if (!tmp) {
		QL_DPRINT11(ha, "Extra PBL is not allocated\n");
		goto done; /* it's OK if second allocation fails, so rc = 0*/
	}

	list_add_tail(&tmp->list_entry, &info->free_pbl_list);

	QL_DPRINT12(ha, "extra pbl_table_pa = %pa\n", &tmp->pa);

done:
	if (rc)
		free_mr_info(dev, info);

	QL_DPRINT12(ha, "exit [%d]\n", rc);

	return rc;
}