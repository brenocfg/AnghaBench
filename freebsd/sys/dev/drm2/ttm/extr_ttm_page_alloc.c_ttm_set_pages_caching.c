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
 int /*<<< orphan*/  printf (char*,unsigned int) ; 
 int set_pages_array_uc (int /*<<< orphan*/ *,unsigned int) ; 
 int set_pages_array_wc (int /*<<< orphan*/ *,unsigned int) ; 
#define  tt_uncached 129 
#define  tt_wc 128 

__attribute__((used)) static int ttm_set_pages_caching(vm_page_t *pages,
		enum ttm_caching_state cstate, unsigned cpages)
{
	int r = 0;
	/* Set page caching */
	switch (cstate) {
	case tt_uncached:
		r = set_pages_array_uc(pages, cpages);
		if (r)
			printf("[TTM] Failed to set %d pages to uc!\n", cpages);
		break;
	case tt_wc:
		r = set_pages_array_wc(pages, cpages);
		if (r)
			printf("[TTM] Failed to set %d pages to wc!\n", cpages);
		break;
	default:
		break;
	}
	return r;
}