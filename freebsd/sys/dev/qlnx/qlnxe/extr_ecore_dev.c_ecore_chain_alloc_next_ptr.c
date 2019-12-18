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
typedef  scalar_t__ u32 ;
struct ecore_dev {int dummy; } ;
struct ecore_chain {scalar_t__ page_cnt; void* p_virt_addr; int /*<<< orphan*/  p_phys_addr; } ;
typedef  enum _ecore_status_t { ____Placeholder__ecore_status_t } _ecore_status_t ;
typedef  int /*<<< orphan*/  dma_addr_t ;

/* Variables and functions */
 int /*<<< orphan*/  DP_NOTICE (struct ecore_dev*,int,char*) ; 
 int /*<<< orphan*/  ECORE_CHAIN_PAGE_SIZE ; 
 int ECORE_NOMEM ; 
 int ECORE_SUCCESS ; 
 void* OSAL_DMA_ALLOC_COHERENT (struct ecore_dev*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 void* OSAL_NULL ; 
 int /*<<< orphan*/  ecore_chain_init_mem (struct ecore_chain*,void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ecore_chain_init_next_ptr_elem (struct ecore_chain*,void*,void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ecore_chain_reset (struct ecore_chain*) ; 

__attribute__((used)) static enum _ecore_status_t
ecore_chain_alloc_next_ptr(struct ecore_dev *p_dev, struct ecore_chain *p_chain)
{
	void *p_virt = OSAL_NULL, *p_virt_prev = OSAL_NULL;
	dma_addr_t p_phys = 0;
	u32 i;

	for (i = 0; i < p_chain->page_cnt; i++) {
		p_virt = OSAL_DMA_ALLOC_COHERENT(p_dev, &p_phys,
						 ECORE_CHAIN_PAGE_SIZE);
		if (!p_virt) {
			DP_NOTICE(p_dev, false,
				  "Failed to allocate chain memory\n");
			return ECORE_NOMEM;
		}

		if (i == 0) {
			ecore_chain_init_mem(p_chain, p_virt, p_phys);
			ecore_chain_reset(p_chain);
		} else {
			ecore_chain_init_next_ptr_elem(p_chain, p_virt_prev,
						       p_virt, p_phys);
		}

		p_virt_prev = p_virt;
	}
	/* Last page's next element should point to the beginning of the
	 * chain.
	 */
	ecore_chain_init_next_ptr_elem(p_chain, p_virt_prev,
				       p_chain->p_virt_addr,
				       p_chain->p_phys_addr);

	return ECORE_SUCCESS;
}