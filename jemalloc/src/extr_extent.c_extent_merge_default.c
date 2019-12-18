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
typedef  int /*<<< orphan*/  tsdn_t ;
typedef  int /*<<< orphan*/  extent_t ;
typedef  int /*<<< orphan*/  extent_hooks_t ;

/* Variables and functions */
 scalar_t__ extent_head_no_merge (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int extent_merge_default_impl (void*,void*) ; 
 int /*<<< orphan*/ * iealloc (int /*<<< orphan*/ *,void*) ; 
 int /*<<< orphan*/  maps_coalesce ; 
 int /*<<< orphan*/ * tsdn_fetch () ; 

__attribute__((used)) static bool
extent_merge_default(extent_hooks_t *extent_hooks, void *addr_a, size_t size_a,
    void *addr_b, size_t size_b, bool committed, unsigned arena_ind) {
	if (!maps_coalesce) {
		tsdn_t *tsdn = tsdn_fetch();
		extent_t *a = iealloc(tsdn, addr_a);
		extent_t *b = iealloc(tsdn, addr_b);
		if (extent_head_no_merge(a, b)) {
			return true;
		}
	}
	return extent_merge_default_impl(addr_a, addr_b);
}