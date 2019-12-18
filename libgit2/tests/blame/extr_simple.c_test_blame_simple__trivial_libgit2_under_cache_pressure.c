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
typedef  int ssize_t ;

/* Variables and functions */
 int git_cache__max_storage ; 
 int /*<<< orphan*/  test_blame_simple__trivial_libgit2 () ; 

void test_blame_simple__trivial_libgit2_under_cache_pressure(void)
{
	ssize_t old_max_storage = git_cache__max_storage;
	git_cache__max_storage = 1024 * 1024;
	test_blame_simple__trivial_libgit2();
	git_cache__max_storage = old_max_storage;
}