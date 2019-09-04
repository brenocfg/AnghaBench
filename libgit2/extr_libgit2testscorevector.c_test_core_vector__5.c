#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int content; } ;
typedef  TYPE_1__ my_struct ;
struct TYPE_8__ {int length; } ;
typedef  TYPE_2__ git_vector ;

/* Variables and functions */
 int _struct_count ; 
 int /*<<< orphan*/  alloc_struct (int) ; 
 int /*<<< orphan*/  cl_assert (int) ; 
 int /*<<< orphan*/  compare_structs ; 
 int /*<<< orphan*/  git__free (scalar_t__) ; 
 int /*<<< orphan*/  git_vector_free (TYPE_2__*) ; 
 scalar_t__ git_vector_get (TYPE_2__*,int) ; 
 int /*<<< orphan*/  git_vector_init (TYPE_2__*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_vector_insert_sorted (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  merge_structs ; 

void test_core_vector__5(void)
{
	git_vector x;
	int i;

	git_vector_init(&x, 1, &compare_structs);

	for (i = 0; i < 10; i += 2)
		git_vector_insert_sorted(&x, alloc_struct(i), &merge_structs);

	for (i = 9; i > 0; i -= 2)
		git_vector_insert_sorted(&x, alloc_struct(i), &merge_structs);

	cl_assert(x.length == 10);
	cl_assert(_struct_count == 10);

	for (i = 0; i < 10; i += 2)
		git_vector_insert_sorted(&x, alloc_struct(i), &merge_structs);

	for (i = 9; i > 0; i -= 2)
		git_vector_insert_sorted(&x, alloc_struct(i), &merge_structs);

	cl_assert(x.length == 10);
	cl_assert(_struct_count == 10);

	for (i = 0; i < 10; ++i) {
		cl_assert(((my_struct *)git_vector_get(&x, i))->content == i);
		git__free(git_vector_get(&x, i));
		_struct_count--;
	}

	git_vector_free(&x);
}