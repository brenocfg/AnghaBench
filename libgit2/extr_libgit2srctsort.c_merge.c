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
struct tsort_store {void** storage; scalar_t__ (* cmp ) (void*,void*,int /*<<< orphan*/ ) ;int /*<<< orphan*/  payload; } ;
struct tsort_run {int length; int start; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  MIN (int const,int const) ; 
 int /*<<< orphan*/  memcpy (void**,void**,int const) ; 
 scalar_t__ resize (struct tsort_store*,int /*<<< orphan*/ ) ; 
 scalar_t__ stub1 (void*,void*,int /*<<< orphan*/ ) ; 
 scalar_t__ stub2 (void*,void*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void merge(void **dst, const struct tsort_run *stack, ssize_t stack_curr, struct tsort_store *store)
{
	const ssize_t A = stack[stack_curr - 2].length;
	const ssize_t B = stack[stack_curr - 1].length;
	const ssize_t curr = stack[stack_curr - 2].start;

	void **storage;
	ssize_t i, j, k;

	if (resize(store, MIN(A, B)) < 0)
		return;

	storage = store->storage;

	/* left merge */
	if (A < B) {
		memcpy(storage, &dst[curr], A * sizeof(void *));
		i = 0;
		j = curr + A;

		for (k = curr; k < curr + A + B; k++) {
			if ((i < A) && (j < curr + A + B)) {
				if (store->cmp(storage[i], dst[j], store->payload) <= 0)
					dst[k] = storage[i++];
				else
					dst[k] = dst[j++];
			} else if (i < A) {
				dst[k] = storage[i++];
			} else
				dst[k] = dst[j++];
		}
	} else {
		memcpy(storage, &dst[curr + A], B * sizeof(void *));
		i = B - 1;
		j = curr + A - 1;

		for (k = curr + A + B - 1; k >= curr; k--) {
			if ((i >= 0) && (j >= curr)) {
				if (store->cmp(dst[j], storage[i], store->payload) > 0)
					dst[k] = dst[j--];
				else
					dst[k] = storage[i--];
			} else if (i >= 0)
				dst[k] = storage[i--];
			else
				dst[k] = dst[j--];
		}
	}
}