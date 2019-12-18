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
typedef  scalar_t__ u64 ;
typedef  int /*<<< orphan*/  u32 ;
struct regpair {void* hi; void* lo; } ;
struct qlnxr_pbl_info {int num_pbes; int pbl_size; } ;
struct qlnxr_pbl {scalar_t__ va; } ;
struct qlnxr_dev {int /*<<< orphan*/ * ha; } ;
struct mr_info {struct qlnxr_pbl_info pbl_info; struct qlnxr_pbl* pbl_table; } ;
struct TYPE_5__ {int page_list_len; TYPE_1__* page_list; } ;
struct TYPE_6__ {TYPE_2__ fast_reg; } ;
struct ib_send_wr {TYPE_3__ wr; } ;
typedef  int /*<<< orphan*/  qlnx_host_t ;
struct TYPE_4__ {scalar_t__* page_list; } ;

/* Variables and functions */
 int /*<<< orphan*/  QL_DPRINT12 (int /*<<< orphan*/ *,char*) ; 
 void* cpu_to_le32 (int /*<<< orphan*/ ) ; 
 scalar_t__ upper_32_bits (scalar_t__) ; 

__attribute__((used)) static void
build_frmr_pbes(struct qlnxr_dev *dev, struct ib_send_wr *wr,
	struct mr_info *info)
{
	int i;
	u64 buf_addr = 0;
	int num_pbes, total_num_pbes = 0;
	struct regpair *pbe;
	struct qlnxr_pbl *pbl_tbl = info->pbl_table;
	struct qlnxr_pbl_info *pbl_info = &info->pbl_info;
	qlnx_host_t	*ha;

	ha = dev->ha;

	QL_DPRINT12(ha, "enter\n");
 
	pbe = (struct regpair *)pbl_tbl->va;
	num_pbes = 0;

	for (i = 0; i < wr->wr.fast_reg.page_list_len; i++) {
		buf_addr = wr->wr.fast_reg.page_list->page_list[i];
		pbe->lo = cpu_to_le32((u32)buf_addr);
		pbe->hi = cpu_to_le32((u32)upper_32_bits(buf_addr));

		num_pbes += 1;
		pbe++;
		total_num_pbes++;

		if (total_num_pbes == pbl_info->num_pbes)
			return;

		/* if the given pbl is full storing the pbes,
		 * move to next pbl.
		 */
		if (num_pbes ==
		    (pbl_info->pbl_size / sizeof(u64))) {
			pbl_tbl++;
			pbe = (struct regpair *)pbl_tbl->va;
			num_pbes = 0;
		}
	}
	QL_DPRINT12(ha, "exit\n");

	return;
}