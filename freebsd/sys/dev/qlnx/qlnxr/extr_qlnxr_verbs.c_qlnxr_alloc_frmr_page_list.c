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
typedef  int /*<<< orphan*/  u64 ;
struct ib_fast_reg_page_list {struct qlnxr_fast_reg_page_list* page_list; } ;
struct qlnxr_fast_reg_page_list {struct ib_fast_reg_page_list ibfrpl; int /*<<< orphan*/  info; struct qlnxr_dev* dev; } ;
struct qlnxr_dev {int /*<<< orphan*/ * ha; } ;
struct ib_device {int dummy; } ;
typedef  int /*<<< orphan*/  qlnx_host_t ;

/* Variables and functions */
 int ENOMEM ; 
 struct ib_fast_reg_page_list* ERR_PTR (int) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  QL_DPRINT11 (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  QL_DPRINT12 (int /*<<< orphan*/ *,char*,...) ; 
 struct qlnxr_dev* get_qlnxr_dev (struct ib_device*) ; 
 int /*<<< orphan*/  kfree (struct qlnxr_fast_reg_page_list*) ; 
 void* kzalloc (int,int /*<<< orphan*/ ) ; 
 int qlnxr_init_mr_info (struct qlnxr_dev*,int /*<<< orphan*/ *,int,int) ; 

struct ib_fast_reg_page_list *
qlnxr_alloc_frmr_page_list(struct ib_device *ibdev, int page_list_len)
{
	struct qlnxr_fast_reg_page_list *frmr_list = NULL;
	struct qlnxr_dev		*dev;
	int				size = page_list_len * sizeof(u64);
	int				rc = -ENOMEM;
	qlnx_host_t			*ha;

	dev = get_qlnxr_dev(ibdev);
	ha = dev->ha;

	QL_DPRINT12(ha, "enter\n");

	frmr_list = kzalloc(sizeof(*frmr_list), GFP_KERNEL);
	if (!frmr_list) {
		QL_DPRINT11(ha, "kzalloc(frmr_list) failed\n");
		goto err;
	}

	frmr_list->dev = dev;
	frmr_list->ibfrpl.page_list = kzalloc(size, GFP_KERNEL);
	if (!frmr_list->ibfrpl.page_list) {
		QL_DPRINT11(ha, "frmr_list->ibfrpl.page_list = NULL failed\n");
		goto err0;
	}

	rc = qlnxr_init_mr_info(dev, &frmr_list->info, page_list_len,
			  1 /* allow dual layer pbl */);
	if (rc)
		goto err1;

	QL_DPRINT12(ha, "exit %p\n", &frmr_list->ibfrpl);

	return &frmr_list->ibfrpl;

err1:
	kfree(frmr_list->ibfrpl.page_list);
err0:
	kfree(frmr_list);
err:
	QL_DPRINT12(ha, "exit with error\n");

	return ERR_PTR(rc);
}