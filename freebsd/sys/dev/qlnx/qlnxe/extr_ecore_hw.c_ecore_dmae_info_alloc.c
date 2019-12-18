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
struct dmae_cmd {int dummy; } ;
typedef  struct dmae_cmd u32 ;
struct TYPE_2__ {int b_mem_ready; int /*<<< orphan*/  channel; int /*<<< orphan*/  intermediate_buffer_phys_addr; int /*<<< orphan*/  dmae_cmd_phys_addr; struct dmae_cmd* p_completion_word; struct dmae_cmd* p_intermediate_buffer; struct dmae_cmd* p_dmae_cmd; int /*<<< orphan*/  completion_word_phys_addr; } ;
struct ecore_hwfn {TYPE_1__ dmae_info; int /*<<< orphan*/  rel_pf_id; int /*<<< orphan*/  p_dev; } ;
typedef  enum _ecore_status_t { ____Placeholder__ecore_status_t } _ecore_status_t ;
typedef  int /*<<< orphan*/  dma_addr_t ;

/* Variables and functions */
 int DMAE_MAX_RW_SIZE ; 
 int /*<<< orphan*/  DP_NOTICE (struct ecore_hwfn*,int,char*) ; 
 int ECORE_NOMEM ; 
 int ECORE_SUCCESS ; 
 struct dmae_cmd* OSAL_DMA_ALLOC_COHERENT (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 struct dmae_cmd* OSAL_NULL ; 
 int /*<<< orphan*/  ecore_dmae_info_free (struct ecore_hwfn*) ; 

enum _ecore_status_t ecore_dmae_info_alloc(struct ecore_hwfn *p_hwfn)
{
	dma_addr_t *p_addr = &p_hwfn->dmae_info.completion_word_phys_addr;
	struct dmae_cmd **p_cmd = &p_hwfn->dmae_info.p_dmae_cmd;
	u32 **p_buff = &p_hwfn->dmae_info.p_intermediate_buffer;
	u32 **p_comp = &p_hwfn->dmae_info.p_completion_word;

	*p_comp = OSAL_DMA_ALLOC_COHERENT(p_hwfn->p_dev, p_addr, sizeof(u32));
	if (*p_comp == OSAL_NULL) {
		DP_NOTICE(p_hwfn, false,
			  "Failed to allocate `p_completion_word'\n");
		goto err;
	}

	p_addr =  &p_hwfn->dmae_info.dmae_cmd_phys_addr;
	*p_cmd = OSAL_DMA_ALLOC_COHERENT(p_hwfn->p_dev, p_addr,
					 sizeof(struct dmae_cmd));
	if (*p_cmd == OSAL_NULL) {
		DP_NOTICE(p_hwfn, false,
			  "Failed to allocate `struct dmae_cmd'\n");
		goto err;
	}

	p_addr = &p_hwfn->dmae_info.intermediate_buffer_phys_addr;
	*p_buff = OSAL_DMA_ALLOC_COHERENT(p_hwfn->p_dev, p_addr,
					  sizeof(u32) * DMAE_MAX_RW_SIZE);
	if (*p_buff == OSAL_NULL) {
		DP_NOTICE(p_hwfn, false,
			  "Failed to allocate `intermediate_buffer'\n");
		goto err;
	}

		p_hwfn->dmae_info.channel = p_hwfn->rel_pf_id;
		p_hwfn->dmae_info.b_mem_ready = true;

	return ECORE_SUCCESS;
err:
	ecore_dmae_info_free(p_hwfn);
	return ECORE_NOMEM;
}