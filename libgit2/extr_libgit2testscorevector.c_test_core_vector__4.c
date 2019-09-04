#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int length; } ;
typedef  TYPE_1__ git_vector ;

/* Variables and functions */
 int /*<<< orphan*/  cl_assert (int) ; 
 int /*<<< orphan*/  compare_them ; 
 int /*<<< orphan*/  git_vector_free (TYPE_1__*) ; 
 void* git_vector_get (TYPE_1__*,intptr_t) ; 
 int /*<<< orphan*/  git_vector_init (TYPE_1__*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_vector_insert_sorted (TYPE_1__*,void*,int /*<<< orphan*/ *) ; 

void test_core_vector__4(void)
{
	git_vector x;
	intptr_t i;
	git_vector_init(&x, 1, &compare_them);

	for (i = 0; i < 10; i += 2) {
		git_vector_insert_sorted(&x, (void*)(i + 1), NULL);
	}

	for (i = 9; i > 0; i -= 2) {
		git_vector_insert_sorted(&x, (void*)(i + 1), NULL);
	}

	for (i = 0; i < 10; i += 2) {
		git_vector_insert_sorted(&x, (void*)(i + 1), NULL);
	}

	for (i = 9; i > 0; i -= 2) {
		git_vector_insert_sorted(&x, (void*)(i + 1), NULL);
	}

	cl_assert(x.length == 20);
	for (i = 0; i < 20; ++i) {
		cl_assert(git_vector_get(&x, i) == (void*)(i / 2 + 1));
	}

	git_vector_free(&x);
}