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
typedef  int u32 ;
struct slow_path_element {int dummy; } ;
struct ecore_spq_entry {int dummy; } ;
struct ecore_spq {int /*<<< orphan*/  chain; int /*<<< orphan*/  lock; int /*<<< orphan*/  p_phys; struct ecore_spq_entry* p_virt; } ;
struct ecore_hwfn {int /*<<< orphan*/  p_dev; struct ecore_spq* p_spq; } ;
typedef  enum _ecore_status_t { ____Placeholder__ecore_status_t } _ecore_status_t ;
typedef  int /*<<< orphan*/  dma_addr_t ;

/* Variables and functions */
 int /*<<< orphan*/  DP_NOTICE (struct ecore_hwfn*,int,char*) ; 
 int /*<<< orphan*/  ECORE_CHAIN_CNT_TYPE_U16 ; 
 int /*<<< orphan*/  ECORE_CHAIN_MODE_SINGLE ; 
 int /*<<< orphan*/  ECORE_CHAIN_USE_TO_PRODUCE ; 
 int ECORE_NOMEM ; 
 int ECORE_SUCCESS ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct ecore_spq_entry* OSAL_DMA_ALLOC_COHERENT (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  OSAL_FREE (int /*<<< orphan*/ ,struct ecore_spq*) ; 
 void* OSAL_NULL ; 
 scalar_t__ OSAL_SPIN_LOCK_ALLOC (struct ecore_hwfn*,int /*<<< orphan*/ *) ; 
 struct ecore_spq* OSAL_ZALLOC (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 scalar_t__ ecore_chain_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,void*) ; 
 int /*<<< orphan*/  ecore_chain_free (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int ecore_chain_get_capacity (int /*<<< orphan*/ *) ; 

enum _ecore_status_t ecore_spq_alloc(struct ecore_hwfn *p_hwfn)
{
	struct ecore_spq_entry *p_virt = OSAL_NULL;
	struct ecore_spq *p_spq = OSAL_NULL;
	dma_addr_t p_phys = 0;
	u32 capacity;

	/* SPQ struct */
	p_spq =
	    OSAL_ZALLOC(p_hwfn->p_dev, GFP_KERNEL, sizeof(struct ecore_spq));
	if (!p_spq) {
		DP_NOTICE(p_hwfn, false, "Failed to allocate `struct ecore_spq'\n");
		return ECORE_NOMEM;
	}

	/* SPQ ring  */
	if (ecore_chain_alloc(p_hwfn->p_dev,
			      ECORE_CHAIN_USE_TO_PRODUCE,
			      ECORE_CHAIN_MODE_SINGLE,
			      ECORE_CHAIN_CNT_TYPE_U16,
			      0, /* N/A when the mode is SINGLE */
			      sizeof(struct slow_path_element),
			      &p_spq->chain, OSAL_NULL)) {
		DP_NOTICE(p_hwfn, false, "Failed to allocate spq chain\n");
		goto spq_allocate_fail;
	}

	/* allocate and fill the SPQ elements (incl. ramrod data list) */
	capacity = ecore_chain_get_capacity(&p_spq->chain);
	p_virt = OSAL_DMA_ALLOC_COHERENT(p_hwfn->p_dev, &p_phys,
					 capacity *
					 sizeof(struct ecore_spq_entry));
	if (!p_virt) {
		goto spq_allocate_fail;
	}

	p_spq->p_virt = p_virt;
	p_spq->p_phys = p_phys;

#ifdef CONFIG_ECORE_LOCK_ALLOC
	if (OSAL_SPIN_LOCK_ALLOC(p_hwfn, &p_spq->lock))
		goto spq_allocate_fail;
#endif

	p_hwfn->p_spq = p_spq;
	return ECORE_SUCCESS;

spq_allocate_fail:
	ecore_chain_free(p_hwfn->p_dev, &p_spq->chain);
	OSAL_FREE(p_hwfn->p_dev, p_spq);
	return ECORE_NOMEM;
}