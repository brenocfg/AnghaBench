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
struct TYPE_7__ {int length; int _alloc_size; void** contents; } ;
typedef  TYPE_1__ git_vector ;

/* Variables and functions */
 int /*<<< orphan*/  assert (TYPE_1__*) ; 
 int /*<<< orphan*/  compute_new_size (TYPE_1__*) ; 
 int /*<<< orphan*/  git_vector_set_sorted (TYPE_1__*,int) ; 
 scalar_t__ resize_vector (TYPE_1__*,int /*<<< orphan*/ ) ; 

int git_vector_insert(git_vector *v, void *element)
{
	assert(v);

	if (v->length >= v->_alloc_size &&
		resize_vector(v, compute_new_size(v)) < 0)
		return -1;

	v->contents[v->length++] = element;

	git_vector_set_sorted(v, v->length <= 1);

	return 0;
}