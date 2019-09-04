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
struct TYPE_6__ {int page_size; } ;
typedef  TYPE_1__ git_pool ;

/* Variables and functions */
 int /*<<< orphan*/  cl_assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_assert_equal_i (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_pool__open_pages (TYPE_1__*) ; 
 int /*<<< orphan*/  git_pool_clear (TYPE_1__*) ; 
 int /*<<< orphan*/  git_pool_init (TYPE_1__*,int) ; 
 int /*<<< orphan*/ * git_pool_malloc (TYPE_1__*,int) ; 

void test_core_pool__1(void)
{
	int i;
	git_pool p;

	git_pool_init(&p, 1);
	p.page_size = 4000;

	for (i = 2010; i > 0; i--)
		cl_assert(git_pool_malloc(&p, i) != NULL);

#ifndef GIT_DEBUG_POOL
	/* with fixed page size, allocation must end up with these values */
	cl_assert_equal_i(591, git_pool__open_pages(&p));
#endif
	git_pool_clear(&p);

	git_pool_init(&p, 1);
	p.page_size = 4120;

	for (i = 2010; i > 0; i--)
		cl_assert(git_pool_malloc(&p, i) != NULL);

#ifndef GIT_DEBUG_POOL
	/* with fixed page size, allocation must end up with these values */
	cl_assert_equal_i(sizeof(void *) == 8 ? 575 : 573, git_pool__open_pages(&p));
#endif
	git_pool_clear(&p);
}