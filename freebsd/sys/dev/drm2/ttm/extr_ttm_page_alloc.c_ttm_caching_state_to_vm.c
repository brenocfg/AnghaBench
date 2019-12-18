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
typedef  int /*<<< orphan*/  vm_memattr_t ;
typedef  enum ttm_caching_state { ____Placeholder_ttm_caching_state } ttm_caching_state ;

/* Variables and functions */
 int /*<<< orphan*/  VM_MEMATTR_UNCACHEABLE ; 
 int /*<<< orphan*/  VM_MEMATTR_WRITE_BACK ; 
 int /*<<< orphan*/  VM_MEMATTR_WRITE_COMBINING ; 
 int /*<<< orphan*/  panic (char*,int) ; 
#define  tt_cached 130 
#define  tt_uncached 129 
#define  tt_wc 128 

__attribute__((used)) static vm_memattr_t
ttm_caching_state_to_vm(enum ttm_caching_state cstate)
{

	switch (cstate) {
	case tt_uncached:
		return (VM_MEMATTR_UNCACHEABLE);
	case tt_wc:
		return (VM_MEMATTR_WRITE_COMBINING);
	case tt_cached:
		return (VM_MEMATTR_WRITE_BACK);
	}
	panic("caching state %d\n", cstate);
}