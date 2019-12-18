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
struct x86_mapping_info {int /*<<< orphan*/  offset; int /*<<< orphan*/  page_flag; int /*<<< orphan*/  alloc_pgt_page; } ;
typedef  int /*<<< orphan*/  pgd_t ;
struct TYPE_2__ {unsigned long start; unsigned long end; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 unsigned long PAGE_SHIFT ; 
 int /*<<< orphan*/  __PAGE_KERNEL_LARGE_EXEC ; 
 int /*<<< orphan*/  __PAGE_OFFSET ; 
 int /*<<< orphan*/  __pa (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  alloc_pgt_page ; 
 scalar_t__ get_safe_page (int /*<<< orphan*/ ) ; 
 int kernel_ident_mapping_init (struct x86_mapping_info*,int /*<<< orphan*/ *,unsigned long,unsigned long) ; 
 int nr_pfn_mapped ; 
 TYPE_1__* pfn_mapped ; 
 int set_up_temporary_text_mapping (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  temp_pgt ; 

__attribute__((used)) static int set_up_temporary_mappings(void)
{
	struct x86_mapping_info info = {
		.alloc_pgt_page	= alloc_pgt_page,
		.page_flag	= __PAGE_KERNEL_LARGE_EXEC,
		.offset		= __PAGE_OFFSET,
	};
	unsigned long mstart, mend;
	pgd_t *pgd;
	int result;
	int i;

	pgd = (pgd_t *)get_safe_page(GFP_ATOMIC);
	if (!pgd)
		return -ENOMEM;

	/* Prepare a temporary mapping for the kernel text */
	result = set_up_temporary_text_mapping(pgd);
	if (result)
		return result;

	/* Set up the direct mapping from scratch */
	for (i = 0; i < nr_pfn_mapped; i++) {
		mstart = pfn_mapped[i].start << PAGE_SHIFT;
		mend   = pfn_mapped[i].end << PAGE_SHIFT;

		result = kernel_ident_mapping_init(&info, pgd, mstart, mend);
		if (result)
			return result;
	}

	temp_pgt = __pa(pgd);
	return 0;
}