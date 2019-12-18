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
struct ref_iterator {int dummy; } ;
struct merge_ref_iterator {int /*<<< orphan*/ * current; void* cb_data; int /*<<< orphan*/ * select; struct ref_iterator* iter1; struct ref_iterator* iter0; struct ref_iterator base; } ;
typedef  int /*<<< orphan*/  ref_iterator_select_fn ;

/* Variables and functions */
 int /*<<< orphan*/  base_ref_iterator_init (struct ref_iterator*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  merge_ref_iterator_vtable ; 
 struct merge_ref_iterator* xcalloc (int,int) ; 

struct ref_iterator *merge_ref_iterator_begin(
		int ordered,
		struct ref_iterator *iter0, struct ref_iterator *iter1,
		ref_iterator_select_fn *select, void *cb_data)
{
	struct merge_ref_iterator *iter = xcalloc(1, sizeof(*iter));
	struct ref_iterator *ref_iterator = &iter->base;

	/*
	 * We can't do the same kind of is_empty_ref_iterator()-style
	 * optimization here as overlay_ref_iterator_begin() does,
	 * because we don't know the semantics of the select function.
	 * It might, for example, implement "intersect" by passing
	 * references through only if they exist in both iterators.
	 */

	base_ref_iterator_init(ref_iterator, &merge_ref_iterator_vtable, ordered);
	iter->iter0 = iter0;
	iter->iter1 = iter1;
	iter->select = select;
	iter->cb_data = cb_data;
	iter->current = NULL;
	return ref_iterator;
}