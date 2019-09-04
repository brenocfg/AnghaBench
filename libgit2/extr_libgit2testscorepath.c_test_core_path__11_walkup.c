#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  ptr; } ;
typedef  TYPE_1__ git_buf ;
struct TYPE_9__ {char** expect; int cancel_after; int expect_idx; } ;
typedef  TYPE_2__ check_walkup_info ;

/* Variables and functions */
 TYPE_1__ GIT_BUF_INIT ; 
 int /*<<< orphan*/  check_one_walkup_step ; 
 int /*<<< orphan*/  cl_assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_assert_equal_s (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_buf_dispose (TYPE_1__*) ; 
 int /*<<< orphan*/  git_buf_sets (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  git_path_walk_up (TYPE_1__*,char*,int /*<<< orphan*/ ,TYPE_2__*) ; 

void test_core_path__11_walkup(void)
{
	git_buf p = GIT_BUF_INIT;

	char *expect[] = {
		/*  1 */ "/a/b/c/d/e/", "/a/b/c/d/", "/a/b/c/", "/a/b/", "/a/", "/", NULL,
		/*  2 */ "/a/b/c/d/e", "/a/b/c/d/", "/a/b/c/", "/a/b/", "/a/", "/", NULL,
		/*  3 */ "/a/b/c/d/e", "/a/b/c/d/", "/a/b/c/", "/a/b/", "/a/", "/", NULL,
		/*  4 */ "/a/b/c/d/e", "/a/b/c/d/", "/a/b/c/", "/a/b/", "/a/", "/", NULL,
		/*  5 */ "/a/b/c/d/e", "/a/b/c/d/", "/a/b/c/", "/a/b/", NULL,
		/*  6 */ "/a/b/c/d/e", "/a/b/c/d/", "/a/b/c/", "/a/b/", NULL,
		/*  7 */ "this_is_a_path", "", NULL,
		/*  8 */ "this_is_a_path/", "", NULL,
		/*  9 */ "///a///b///c///d///e///", "///a///b///c///d///", "///a///b///c///", "///a///b///", "///a///", "///", NULL,
		/* 10 */ "a/b/c/", "a/b/", "a/", "", NULL,
		/* 11 */ "a/b/c", "a/b/", "a/", "", NULL,
		/* 12 */ "a/b/c/", "a/b/", "a/", NULL,
		/* 13 */ "", NULL,
		/* 14 */ "/", NULL,
		/* 15 */ NULL
	};

	char *root[] = {
		/*  1 */ NULL,
		/*  2 */ NULL,
		/*  3 */ "/",
		/*  4 */ "",
		/*  5 */ "/a/b",
		/*  6 */ "/a/b/",
		/*  7 */ NULL,
		/*  8 */ NULL,
		/*  9 */ NULL,
		/* 10 */ NULL,
		/* 11 */ NULL,
		/* 12 */ "a/",
		/* 13 */ NULL,
		/* 14 */ NULL,
	};

	int i, j;
	check_walkup_info info;

	info.expect = expect;
	info.cancel_after = -1;

	for (i = 0, j = 0; expect[i] != NULL; i++, j++) {

		git_buf_sets(&p, expect[i]);

		info.expect_idx = i;
		cl_git_pass(
			git_path_walk_up(&p, root[j], check_one_walkup_step, &info)
		);

		cl_assert_equal_s(p.ptr, expect[i]);
		cl_assert(expect[info.expect_idx] == NULL);
		i = info.expect_idx;
	}

	git_buf_dispose(&p);
}