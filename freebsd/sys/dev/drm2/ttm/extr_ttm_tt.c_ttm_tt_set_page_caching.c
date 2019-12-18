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
typedef  int /*<<< orphan*/  vm_page_t ;
typedef  enum ttm_caching_state { ____Placeholder_ttm_caching_state } ttm_caching_state ;

/* Variables and functions */
 int /*<<< orphan*/  VM_MEMATTR_UNCACHEABLE ; 
 int /*<<< orphan*/  VM_MEMATTR_WRITE_BACK ; 
 int /*<<< orphan*/  VM_MEMATTR_WRITE_COMBINING ; 
 int /*<<< orphan*/  pmap_page_set_memattr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int tt_cached ; 
 int tt_uncached ; 
 int tt_wc ; 

__attribute__((used)) static inline int ttm_tt_set_page_caching(vm_page_t p,
					  enum ttm_caching_state c_old,
					  enum ttm_caching_state c_new)
{

	/* XXXKIB our VM does not need this. */
#if 0
	if (c_old != tt_cached) {
		/* p isn't in the default caching state, set it to
		 * writeback first to free its current memtype. */
		pmap_page_set_memattr(p, VM_MEMATTR_WRITE_BACK);
	}
#endif

	if (c_new == tt_wc)
		pmap_page_set_memattr(p, VM_MEMATTR_WRITE_COMBINING);
	else if (c_new == tt_uncached)
		pmap_page_set_memattr(p, VM_MEMATTR_UNCACHEABLE);

	return (0);
}