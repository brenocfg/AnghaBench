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
typedef  int /*<<< orphan*/  git_pool ;

/* Variables and functions */
 int /*<<< orphan*/  cl_assert (int) ; 
 int git_pool__ptr_in_pool (int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  git_pool_clear (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_pool_init (int /*<<< orphan*/ *,int) ; 
 void* git_pool_malloc (int /*<<< orphan*/ *,int) ; 

void test_core_pool__0(void)
{
	int i;
	git_pool p;
	void *ptr;

	git_pool_init(&p, 1);

	for (i = 1; i < 10000; i *= 2) {
		ptr = git_pool_malloc(&p, i);
		cl_assert(ptr != NULL);
		cl_assert(git_pool__ptr_in_pool(&p, ptr));
		cl_assert(!git_pool__ptr_in_pool(&p, &i));
	}

	git_pool_clear(&p);
}