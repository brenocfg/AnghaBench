#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {size_t length; size_t _alloc_size; void** contents; scalar_t__ _cmp; } ;
typedef  TYPE_1__ git_vector ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  compute_new_size (TYPE_1__*) ; 
 int /*<<< orphan*/  git__bsearch (void**,size_t,void*,scalar_t__,size_t*) ; 
 int /*<<< orphan*/  git_vector_is_sorted (TYPE_1__*) ; 
 int /*<<< orphan*/  git_vector_sort (TYPE_1__*) ; 
 int /*<<< orphan*/  memmove (void**,void**,size_t) ; 
 scalar_t__ resize_vector (TYPE_1__*,int /*<<< orphan*/ ) ; 

int git_vector_insert_sorted(
	git_vector *v, void *element, int (*on_dup)(void **old, void *new))
{
	int result;
	size_t pos;

	assert(v && v->_cmp);

	if (!git_vector_is_sorted(v))
		git_vector_sort(v);

	if (v->length >= v->_alloc_size &&
		resize_vector(v, compute_new_size(v)) < 0)
		return -1;

	/* If we find the element and have a duplicate handler callback,
	 * invoke it.  If it returns non-zero, then cancel insert, otherwise
	 * proceed with normal insert.
	 */
	if (!git__bsearch(v->contents, v->length, element, v->_cmp, &pos) &&
		on_dup && (result = on_dup(&v->contents[pos], element)) < 0)
		return result;

	/* shift elements to the right */
	if (pos < v->length)
		memmove(v->contents + pos + 1, v->contents + pos,
		        (v->length - pos) * sizeof(void *));

	v->contents[pos] = element;
	v->length++;

	return 0;
}