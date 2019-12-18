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
struct slice_mask {unsigned long low_slices; int /*<<< orphan*/  high_slices; } ;
struct mm_struct {int /*<<< orphan*/  context; } ;

/* Variables and functions */
 int /*<<< orphan*/  SLB_ADDR_LIMIT_DEFAULT ; 
 int SLICE_NUM_HIGH ; 
 int SLICE_NUM_LOW ; 
 int /*<<< orphan*/  bitmap_fill (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memset (unsigned char*,unsigned int,int) ; 
 unsigned char* mm_ctx_high_slices (int /*<<< orphan*/ *) ; 
 unsigned char* mm_ctx_low_slices (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mm_ctx_set_slb_addr_limit (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mm_ctx_set_user_psize (int /*<<< orphan*/ *,unsigned int) ; 
 unsigned int mmu_virtual_psize ; 
 int /*<<< orphan*/  slice_dbg (char*,struct mm_struct*) ; 
 struct slice_mask* slice_mask_for_size (int /*<<< orphan*/ *,unsigned int) ; 

void slice_init_new_context_exec(struct mm_struct *mm)
{
	unsigned char *hpsizes, *lpsizes;
	struct slice_mask *mask;
	unsigned int psize = mmu_virtual_psize;

	slice_dbg("slice_init_new_context_exec(mm=%p)\n", mm);

	/*
	 * In the case of exec, use the default limit. In the
	 * case of fork it is just inherited from the mm being
	 * duplicated.
	 */
	mm_ctx_set_slb_addr_limit(&mm->context, SLB_ADDR_LIMIT_DEFAULT);
	mm_ctx_set_user_psize(&mm->context, psize);

	/*
	 * Set all slice psizes to the default.
	 */
	lpsizes = mm_ctx_low_slices(&mm->context);
	memset(lpsizes, (psize << 4) | psize, SLICE_NUM_LOW >> 1);

	hpsizes = mm_ctx_high_slices(&mm->context);
	memset(hpsizes, (psize << 4) | psize, SLICE_NUM_HIGH >> 1);

	/*
	 * Slice mask cache starts zeroed, fill the default size cache.
	 */
	mask = slice_mask_for_size(&mm->context, psize);
	mask->low_slices = ~0UL;
	if (SLICE_NUM_HIGH)
		bitmap_fill(mask->high_slices, SLICE_NUM_HIGH);
}