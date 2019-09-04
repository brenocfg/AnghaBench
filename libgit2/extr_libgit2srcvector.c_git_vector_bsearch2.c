#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ git_vector_cmp ;
struct TYPE_4__ {int /*<<< orphan*/  length; int /*<<< orphan*/  contents; int /*<<< orphan*/  _cmp; } ;
typedef  TYPE_1__ git_vector ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int git__bsearch (int /*<<< orphan*/ ,int /*<<< orphan*/ ,void const*,scalar_t__,size_t*) ; 
 int /*<<< orphan*/  git_vector_sort (TYPE_1__*) ; 

int git_vector_bsearch2(
	size_t *at_pos,
	git_vector *v,
	git_vector_cmp key_lookup,
	const void *key)
{
	assert(v && key && key_lookup);

	/* need comparison function to sort the vector */
	if (!v->_cmp)
		return -1;

	git_vector_sort(v);

	return git__bsearch(v->contents, v->length, key, key_lookup, at_pos);
}