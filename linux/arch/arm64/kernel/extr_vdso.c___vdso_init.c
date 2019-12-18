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
struct page {int dummy; } ;
typedef  enum arch_vdso_type { ____Placeholder_arch_vdso_type } arch_vdso_type ;
struct TYPE_6__ {int vdso_code_start; int vdso_pages; int vdso_code_end; TYPE_2__* cm; TYPE_1__* dm; } ;
struct TYPE_5__ {struct page** pages; } ;
struct TYPE_4__ {struct page** pages; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int PAGE_SHIFT ; 
 int /*<<< orphan*/  __pa_symbol (int /*<<< orphan*/ ) ; 
 struct page** kcalloc (int,int,int /*<<< orphan*/ ) ; 
 scalar_t__ memcmp (int,char*,int) ; 
 struct page* pfn_to_page (unsigned long) ; 
 struct page* phys_to_page (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 unsigned long sym_to_pfn (int) ; 
 int /*<<< orphan*/  vdso_data ; 
 TYPE_3__* vdso_lookup ; 

__attribute__((used)) static int __vdso_init(enum arch_vdso_type arch_index)
{
	int i;
	struct page **vdso_pagelist;
	unsigned long pfn;

	if (memcmp(vdso_lookup[arch_index].vdso_code_start, "\177ELF", 4)) {
		pr_err("vDSO is not a valid ELF object!\n");
		return -EINVAL;
	}

	vdso_lookup[arch_index].vdso_pages = (
			vdso_lookup[arch_index].vdso_code_end -
			vdso_lookup[arch_index].vdso_code_start) >>
			PAGE_SHIFT;

	/* Allocate the vDSO pagelist, plus a page for the data. */
	vdso_pagelist = kcalloc(vdso_lookup[arch_index].vdso_pages + 1,
				sizeof(struct page *),
				GFP_KERNEL);
	if (vdso_pagelist == NULL)
		return -ENOMEM;

	/* Grab the vDSO data page. */
	vdso_pagelist[0] = phys_to_page(__pa_symbol(vdso_data));


	/* Grab the vDSO code pages. */
	pfn = sym_to_pfn(vdso_lookup[arch_index].vdso_code_start);

	for (i = 0; i < vdso_lookup[arch_index].vdso_pages; i++)
		vdso_pagelist[i + 1] = pfn_to_page(pfn + i);

	vdso_lookup[arch_index].dm->pages = &vdso_pagelist[0];
	vdso_lookup[arch_index].cm->pages = &vdso_pagelist[1];

	return 0;
}