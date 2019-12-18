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
typedef  scalar_t__ vm_page_t ;
struct pglist {int dummy; } ;
typedef  enum ttm_caching_state { ____Placeholder_ttm_caching_state } ttm_caching_state ;
struct TYPE_2__ {int /*<<< orphan*/  q; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  M_TEMP ; 
 int M_WAITOK ; 
 int M_ZERO ; 
 int PAGE_SIZE ; 
 int /*<<< orphan*/  PageHighMem (scalar_t__) ; 
 int /*<<< orphan*/  TAILQ_INSERT_HEAD (struct pglist*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (scalar_t__*,int /*<<< orphan*/ ) ; 
 scalar_t__* malloc (unsigned int,int /*<<< orphan*/ ,int) ; 
 unsigned int min (unsigned int,unsigned int) ; 
 TYPE_1__ plinks ; 
 int /*<<< orphan*/  printf (char*,unsigned int) ; 
 int /*<<< orphan*/  ttm_handle_caching_state_failure (struct pglist*,int,int,scalar_t__*,unsigned int) ; 
 int ttm_set_pages_caching (scalar_t__*,int,unsigned int) ; 
 scalar_t__ ttm_vm_page_alloc (int,int) ; 

__attribute__((used)) static int ttm_alloc_new_pages(struct pglist *pages, int ttm_alloc_flags,
		int ttm_flags, enum ttm_caching_state cstate, unsigned count)
{
	vm_page_t *caching_array;
	vm_page_t p;
	int r = 0;
	unsigned i, cpages;
	unsigned max_cpages = min(count,
			(unsigned)(PAGE_SIZE/sizeof(vm_page_t)));

	/* allocate array for page caching change */
	caching_array = malloc(max_cpages * sizeof(vm_page_t), M_TEMP,
	    M_WAITOK | M_ZERO);

	for (i = 0, cpages = 0; i < count; ++i) {
		p = ttm_vm_page_alloc(ttm_alloc_flags, cstate);
		if (!p) {
			printf("[TTM] Unable to get page %u\n", i);

			/* store already allocated pages in the pool after
			 * setting the caching state */
			if (cpages) {
				r = ttm_set_pages_caching(caching_array,
							  cstate, cpages);
				if (r)
					ttm_handle_caching_state_failure(pages,
						ttm_flags, cstate,
						caching_array, cpages);
			}
			r = -ENOMEM;
			goto out;
		}

#ifdef CONFIG_HIGHMEM /* KIB: nop */
		/* gfp flags of highmem page should never be dma32 so we
		 * we should be fine in such case
		 */
		if (!PageHighMem(p))
#endif
		{
			caching_array[cpages++] = p;
			if (cpages == max_cpages) {

				r = ttm_set_pages_caching(caching_array,
						cstate, cpages);
				if (r) {
					ttm_handle_caching_state_failure(pages,
						ttm_flags, cstate,
						caching_array, cpages);
					goto out;
				}
				cpages = 0;
			}
		}

		TAILQ_INSERT_HEAD(pages, p, plinks.q);
	}

	if (cpages) {
		r = ttm_set_pages_caching(caching_array, cstate, cpages);
		if (r)
			ttm_handle_caching_state_failure(pages,
					ttm_flags, cstate,
					caching_array, cpages);
	}
out:
	free(caching_array, M_TEMP);

	return r;
}