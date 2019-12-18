#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  grealloc; int /*<<< orphan*/  gmalloc; } ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_OPT_SET_ALLOCATOR ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_libgit2_opts (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  git_stdalloc_init_allocator (TYPE_1__*) ; 
 TYPE_1__ oom_alloc ; 
 int /*<<< orphan*/  oom_malloc ; 
 int /*<<< orphan*/  oom_realloc ; 
 TYPE_1__ std_alloc ; 

void test_buf_oom__initialize(void)
{
	git_stdalloc_init_allocator(&std_alloc);
	git_stdalloc_init_allocator(&oom_alloc);

	oom_alloc.gmalloc = oom_malloc;
	oom_alloc.grealloc = oom_realloc;

	cl_git_pass(git_libgit2_opts(GIT_OPT_SET_ALLOCATOR, &oom_alloc));
}