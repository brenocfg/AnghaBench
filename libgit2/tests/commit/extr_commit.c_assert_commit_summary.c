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
struct git_commit {int dummy; } ;
struct TYPE_6__ {int /*<<< orphan*/  raw_message; } ;
typedef  TYPE_1__ git_commit ;

/* Variables and functions */
 int /*<<< orphan*/  cl_assert (TYPE_1__*) ; 
 int /*<<< orphan*/  cl_assert_equal_s (char const*,int /*<<< orphan*/ ) ; 
 TYPE_1__* git__calloc (int,int) ; 
 int /*<<< orphan*/  git__strdup (char const*) ; 
 int /*<<< orphan*/  git_commit__free (TYPE_1__*) ; 
 int /*<<< orphan*/  git_commit_summary (TYPE_1__*) ; 

void assert_commit_summary(const char *expected, const char *given)
{
	git_commit *dummy;

	cl_assert(dummy = git__calloc(1, sizeof(struct git_commit)));

	dummy->raw_message = git__strdup(given);
	cl_assert_equal_s(expected, git_commit_summary(dummy));

	git_commit__free(dummy);
}