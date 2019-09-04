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
struct tsort_store {void* payload; int /*<<< orphan*/  cmp; int /*<<< orphan*/ * storage; scalar_t__ alloc; } ;
struct tsort_run {int dummy; } ;
typedef  scalar_t__ ssize_t ;
typedef  int /*<<< orphan*/  git__sort_r_cmp ;

/* Variables and functions */
 int /*<<< orphan*/  PUSH_NEXT () ; 
 int /*<<< orphan*/  bisort (void**,int,size_t,int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  check_invariant (struct tsort_run*,scalar_t__) ; 
 scalar_t__ collapse (void**,struct tsort_run*,scalar_t__,struct tsort_store*,size_t) ; 
 scalar_t__ compute_minrun (size_t) ; 

void git__tsort_r(
	void **dst, size_t size, git__sort_r_cmp cmp, void *payload)
{
	struct tsort_store _store, *store = &_store;
	struct tsort_run run_stack[128];

	ssize_t stack_curr = 0;
	ssize_t len, run;
	ssize_t curr = 0;
	ssize_t minrun;

	if (size < 64) {
		bisort(dst, 1, size, cmp, payload);
		return;
	}

	/* compute the minimum run length */
	minrun = (ssize_t)compute_minrun(size);

	/* temporary storage for merges */
	store->alloc = 0;
	store->storage = NULL;
	store->cmp = cmp;
	store->payload = payload;

	PUSH_NEXT();
	PUSH_NEXT();
	PUSH_NEXT();

	while (1) {
		if (!check_invariant(run_stack, stack_curr)) {
			stack_curr = collapse(dst, run_stack, stack_curr, store, size);
			continue;
		}

		PUSH_NEXT();
	}
}