#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
typedef  size_t u32 ;
struct ecore_dev {int dummy; } ;
struct TYPE_4__ {void** pp_virt_addr_tbl; } ;
struct TYPE_3__ {void* p_virt_table; int /*<<< orphan*/  p_phys_table; } ;
struct ecore_chain {size_t page_cnt; TYPE_2__ pbl; TYPE_1__ pbl_sp; int /*<<< orphan*/  b_external_pbl; } ;
typedef  int /*<<< orphan*/  dma_addr_t ;

/* Variables and functions */
 size_t ECORE_CHAIN_PAGE_SIZE ; 
 size_t ECORE_CHAIN_PBL_ENTRY_SIZE ; 
 int /*<<< orphan*/  OSAL_DMA_FREE_COHERENT (struct ecore_dev*,void*,int /*<<< orphan*/ ,size_t) ; 
 void** OSAL_NULL ; 
 int /*<<< orphan*/  OSAL_VFREE (struct ecore_dev*,void**) ; 

__attribute__((used)) static void ecore_chain_free_pbl(struct ecore_dev *p_dev,
				 struct ecore_chain *p_chain)
{
	void **pp_virt_addr_tbl = p_chain->pbl.pp_virt_addr_tbl;
	u8 *p_pbl_virt = (u8 *)p_chain->pbl_sp.p_virt_table;
	u32 page_cnt = p_chain->page_cnt, i, pbl_size;

	if (!pp_virt_addr_tbl)
		return;

	if (!p_pbl_virt)
		goto out;

	for (i = 0; i < page_cnt; i++) {
		if (!pp_virt_addr_tbl[i])
			break;

		OSAL_DMA_FREE_COHERENT(p_dev, pp_virt_addr_tbl[i],
				       *(dma_addr_t *)p_pbl_virt,
				       ECORE_CHAIN_PAGE_SIZE);

		p_pbl_virt += ECORE_CHAIN_PBL_ENTRY_SIZE;
	}

	pbl_size = page_cnt * ECORE_CHAIN_PBL_ENTRY_SIZE;

	if (!p_chain->b_external_pbl) {
		OSAL_DMA_FREE_COHERENT(p_dev, p_chain->pbl_sp.p_virt_table,
				       p_chain->pbl_sp.p_phys_table, pbl_size);
	}
out:
	OSAL_VFREE(p_dev, p_chain->pbl.pp_virt_addr_tbl);
	p_chain->pbl.pp_virt_addr_tbl = OSAL_NULL;
}