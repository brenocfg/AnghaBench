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
struct ib_mr {int dummy; } ;
struct qlnxr_mr {struct ib_mr ibmr; } ;
struct qlnxr_dev {int /*<<< orphan*/ * ha; } ;
struct ib_pd {int /*<<< orphan*/  device; } ;
typedef  int /*<<< orphan*/  qlnx_host_t ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 struct ib_mr* ERR_PTR (int /*<<< orphan*/ ) ; 
 scalar_t__ IS_ERR (struct qlnxr_mr*) ; 
 int /*<<< orphan*/  QL_DPRINT12 (int /*<<< orphan*/ *,char*,...) ; 
 struct qlnxr_mr* __qlnxr_alloc_mr (struct ib_pd*,int) ; 
 struct qlnxr_dev* get_qlnxr_dev (int /*<<< orphan*/ ) ; 

struct ib_mr *
qlnxr_alloc_frmr(struct ib_pd *ibpd, int max_page_list_len)
{
	struct qlnxr_dev *dev;
	struct qlnxr_mr *mr;
	qlnx_host_t	*ha;
	struct ib_mr *ibmr = NULL;

	dev = get_qlnxr_dev((ibpd->device));
	ha = dev->ha;

	QL_DPRINT12(ha, "enter\n");

	mr = __qlnxr_alloc_mr(ibpd, max_page_list_len);

	if (IS_ERR(mr)) {
		ibmr = ERR_PTR(-EINVAL);
	} else {
		ibmr = &mr->ibmr;
	}

	QL_DPRINT12(ha, "exit %p\n", ibmr);
	return (ibmr);
}