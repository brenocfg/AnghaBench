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
 int /*<<< orphan*/  cl_assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_pool_clear (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_pool_init (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * git_pool_strndup (int /*<<< orphan*/ *,char*,size_t) ; 

void test_core_pool__strndup_limit(void)
{
	git_pool p;

	git_pool_init(&p, 1);
	/* ensure 64 bit doesn't overflow */
	cl_assert(git_pool_strndup(&p, "foo", (size_t)-1) == NULL);
	git_pool_clear(&p);
}