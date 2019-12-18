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
typedef  int /*<<< orphan*/  vm_page_t ;
struct pglist {int dummy; } ;
typedef  enum ttm_caching_state { ____Placeholder_ttm_caching_state } ttm_caching_state ;
struct TYPE_2__ {int /*<<< orphan*/  q; } ;

/* Variables and functions */
 int /*<<< orphan*/  TAILQ_REMOVE (struct pglist*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__ plinks ; 
 int /*<<< orphan*/  ttm_vm_page_free (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ttm_handle_caching_state_failure(struct pglist *pages,
		int ttm_flags, enum ttm_caching_state cstate,
		vm_page_t *failed_pages, unsigned cpages)
{
	unsigned i;
	/* Failed pages have to be freed */
	for (i = 0; i < cpages; ++i) {
		TAILQ_REMOVE(pages, failed_pages[i], plinks.q);
		ttm_vm_page_free(failed_pages[i]);
	}
}