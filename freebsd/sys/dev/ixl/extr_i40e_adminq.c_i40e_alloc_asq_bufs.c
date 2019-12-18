#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {scalar_t__ va; } ;
struct TYPE_6__ {struct i40e_dma_mem* asq_bi; } ;
struct TYPE_7__ {TYPE_4__ dma_head; TYPE_1__ r; } ;
struct TYPE_8__ {int num_asq_entries; TYPE_2__ asq; int /*<<< orphan*/  asq_buf_size; } ;
struct i40e_hw {TYPE_3__ aq; } ;
struct i40e_dma_mem {int dummy; } ;
typedef  enum i40e_status_code { ____Placeholder_i40e_status_code } i40e_status_code ;

/* Variables and functions */
 int /*<<< orphan*/  I40E_ADMINQ_DESC_ALIGNMENT ; 
 int i40e_allocate_dma_mem (struct i40e_hw*,struct i40e_dma_mem*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int i40e_allocate_virt_mem (struct i40e_hw*,TYPE_4__*,int) ; 
 int /*<<< orphan*/  i40e_free_dma_mem (struct i40e_hw*,struct i40e_dma_mem*) ; 
 int /*<<< orphan*/  i40e_free_virt_mem (struct i40e_hw*,TYPE_4__*) ; 
 int /*<<< orphan*/  i40e_mem_asq_buf ; 

__attribute__((used)) static enum i40e_status_code i40e_alloc_asq_bufs(struct i40e_hw *hw)
{
	enum i40e_status_code ret_code;
	struct i40e_dma_mem *bi;
	int i;

	/* No mapped memory needed yet, just the buffer info structures */
	ret_code = i40e_allocate_virt_mem(hw, &hw->aq.asq.dma_head,
		(hw->aq.num_asq_entries * sizeof(struct i40e_dma_mem)));
	if (ret_code)
		goto alloc_asq_bufs;
	hw->aq.asq.r.asq_bi = (struct i40e_dma_mem *)hw->aq.asq.dma_head.va;

	/* allocate the mapped buffers */
	for (i = 0; i < hw->aq.num_asq_entries; i++) {
		bi = &hw->aq.asq.r.asq_bi[i];
		ret_code = i40e_allocate_dma_mem(hw, bi,
						 i40e_mem_asq_buf,
						 hw->aq.asq_buf_size,
						 I40E_ADMINQ_DESC_ALIGNMENT);
		if (ret_code)
			goto unwind_alloc_asq_bufs;
	}
alloc_asq_bufs:
	return ret_code;

unwind_alloc_asq_bufs:
	/* don't try to free the one that failed... */
	i--;
	for (; i >= 0; i--)
		i40e_free_dma_mem(hw, &hw->aq.asq.r.asq_bi[i]);
	i40e_free_virt_mem(hw, &hw->aq.asq.dma_head);

	return ret_code;
}