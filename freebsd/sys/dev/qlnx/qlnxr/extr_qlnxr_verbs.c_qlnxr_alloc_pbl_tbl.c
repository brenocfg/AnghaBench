#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct qlnxr_pbl_info {int num_pbls; int /*<<< orphan*/  pbl_size; } ;
struct qlnxr_pbl {int /*<<< orphan*/  pa; void* va; } ;
struct qlnxr_dev {TYPE_1__* ha; } ;
struct TYPE_4__ {int /*<<< orphan*/  cdev; } ;
typedef  TYPE_1__ qlnx_host_t ;
typedef  int /*<<< orphan*/  gfp_t ;
typedef  int /*<<< orphan*/  dma_addr_t ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  QL_DPRINT11 (TYPE_1__*,char*,int) ; 
 int /*<<< orphan*/  QL_DPRINT12 (TYPE_1__*,char*) ; 
 struct qlnxr_pbl* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 void* qlnx_dma_alloc_coherent (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qlnxr_free_pbl (struct qlnxr_dev*,struct qlnxr_pbl_info*,struct qlnxr_pbl*) ; 

__attribute__((used)) static struct qlnxr_pbl *
qlnxr_alloc_pbl_tbl(struct qlnxr_dev *dev,
	struct qlnxr_pbl_info *pbl_info, gfp_t flags)
{
	void			*va;
	dma_addr_t		pa;
	dma_addr_t		*pbl_main_tbl;
	struct qlnxr_pbl	*pbl_table;
	int			i, rc = 0;
	qlnx_host_t		*ha;

	ha = dev->ha;

	QL_DPRINT12(ha, "enter\n");

	pbl_table = kzalloc(sizeof(*pbl_table) * pbl_info->num_pbls, flags);

	if (!pbl_table) {
		QL_DPRINT12(ha, "pbl_table = NULL\n");
		return NULL;
	}

	for (i = 0; i < pbl_info->num_pbls; i++) {
		va = qlnx_dma_alloc_coherent(&dev->ha->cdev, &pa, pbl_info->pbl_size);
		if (!va) {
			QL_DPRINT11(ha, "Failed to allocate pbl#%d\n", i);
			rc = -ENOMEM;
			goto err;
		}
		memset(va, 0, pbl_info->pbl_size);
		pbl_table[i].va = va;
		pbl_table[i].pa = pa;
	}

	/* Two-Layer PBLs, if we have more than one pbl we need to initialize
	 * the first one with physical pointers to all of the rest
	 */
	pbl_main_tbl = (dma_addr_t *)pbl_table[0].va;
	for (i = 0; i < pbl_info->num_pbls - 1; i++)
		pbl_main_tbl[i] = pbl_table[i + 1].pa;

	QL_DPRINT12(ha, "exit\n");
	return pbl_table;

err:
	qlnxr_free_pbl(dev, pbl_info, pbl_table);

	QL_DPRINT12(ha, "exit with error\n");
	return NULL;
}