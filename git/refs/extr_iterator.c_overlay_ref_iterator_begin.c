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
struct ref_iterator {int /*<<< orphan*/  ordered; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG (char*) ; 
 scalar_t__ is_empty_ref_iterator (struct ref_iterator*) ; 
 struct ref_iterator* merge_ref_iterator_begin (int,struct ref_iterator*,struct ref_iterator*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  overlay_iterator_select ; 
 int /*<<< orphan*/  ref_iterator_abort (struct ref_iterator*) ; 

struct ref_iterator *overlay_ref_iterator_begin(
		struct ref_iterator *front, struct ref_iterator *back)
{
	/*
	 * Optimization: if one of the iterators is empty, return the
	 * other one rather than incurring the overhead of wrapping
	 * them.
	 */
	if (is_empty_ref_iterator(front)) {
		ref_iterator_abort(front);
		return back;
	} else if (is_empty_ref_iterator(back)) {
		ref_iterator_abort(back);
		return front;
	} else if (!front->ordered || !back->ordered) {
		BUG("overlay_ref_iterator requires ordered inputs");
	}

	return merge_ref_iterator_begin(1, front, back,
					overlay_iterator_select, NULL);
}