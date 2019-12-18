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
typedef  scalar_t__ uint32_t ;
struct unwind_idx {int /*<<< orphan*/  offset; } ;
struct search_context {int /*<<< orphan*/ * exidx_end; int /*<<< orphan*/ * exidx_start; scalar_t__ addr; } ;
typedef  int /*<<< orphan*/  sc ;
typedef  scalar_t__ int32_t ;
typedef  int /*<<< orphan*/ * caddr_t ;

/* Variables and functions */
 int /*<<< orphan*/  bzero (struct search_context*,int) ; 
 int /*<<< orphan*/  exidx_end ; 
 int /*<<< orphan*/  exidx_start ; 
 scalar_t__ expand_prel31 (int /*<<< orphan*/ ) ; 
 scalar_t__ linker_file_foreach (int /*<<< orphan*/ ,struct search_context*) ; 
 int /*<<< orphan*/  module_search ; 

__attribute__((used)) static struct unwind_idx *
find_index(uint32_t addr, int search_modules)
{
	struct search_context sc;
	caddr_t idx_start, idx_end;
	unsigned int min, mid, max;
	struct unwind_idx *start;
	struct unwind_idx *item;
	int32_t prel31_addr;
	uint32_t func_addr;

	start = (struct unwind_idx *)&exidx_start;
	idx_start = (caddr_t)&exidx_start;
	idx_end = (caddr_t)&exidx_end;

	/* This may acquire a lock */
	if (search_modules) {
		bzero(&sc, sizeof(sc));
		sc.addr = addr;
		if (linker_file_foreach(module_search, &sc) != 0 &&
		   sc.exidx_start != NULL && sc.exidx_end != NULL) {
			start = (struct unwind_idx *)sc.exidx_start;
			idx_start = sc.exidx_start;
			idx_end = sc.exidx_end;
		}
	}

	min = 0;
	max = (idx_end - idx_start) / sizeof(struct unwind_idx);

	while (min != max) {
		mid = min + (max - min + 1) / 2;

		item = &start[mid];

		prel31_addr = expand_prel31(item->offset);
		func_addr = (uint32_t)&item->offset + prel31_addr;

		if (func_addr <= addr) {
			min = mid;
		} else {
			max = mid - 1;
		}
	}

	return &start[min];
}