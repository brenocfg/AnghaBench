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
struct topa {scalar_t__ last; } ;
struct topa_page {struct topa topa; } ;
struct page {int dummy; } ;
typedef  int gfp_t ;
struct TYPE_2__ {int base; int end; } ;

/* Variables and functions */
 int /*<<< orphan*/  PT_CAP_topa_multiple_entries ; 
 TYPE_1__* TOPA_ENTRY (struct topa*,int) ; 
 int TOPA_SHIFT ; 
 int __GFP_ZERO ; 
 struct page* alloc_pages_node (int,int,int /*<<< orphan*/ ) ; 
 int cpu_to_node (int) ; 
 int /*<<< orphan*/  intel_pt_validate_hw_cap (int /*<<< orphan*/ ) ; 
 struct topa_page* page_address (struct page*) ; 
 int page_to_phys (struct page*) ; 

__attribute__((used)) static struct topa *topa_alloc(int cpu, gfp_t gfp)
{
	int node = cpu_to_node(cpu);
	struct topa_page *tp;
	struct page *p;

	p = alloc_pages_node(node, gfp | __GFP_ZERO, 0);
	if (!p)
		return NULL;

	tp = page_address(p);
	tp->topa.last = 0;

	/*
	 * In case of singe-entry ToPA, always put the self-referencing END
	 * link as the 2nd entry in the table
	 */
	if (!intel_pt_validate_hw_cap(PT_CAP_topa_multiple_entries)) {
		TOPA_ENTRY(&tp->topa, 1)->base = page_to_phys(p) >> TOPA_SHIFT;
		TOPA_ENTRY(&tp->topa, 1)->end = 1;
	}

	return &tp->topa;
}