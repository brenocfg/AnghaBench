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
typedef  int /*<<< orphan*/  git_repository ;
typedef  int /*<<< orphan*/  git_reference ;

/* Variables and functions */
 int /*<<< orphan*/  cl_assert_equal_s (int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_reference_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_reference_lookup (int /*<<< orphan*/ **,int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  git_reference_shorthand (int /*<<< orphan*/ *) ; 

void assert_shorthand(git_repository *repo, const char *refname, const char *shorthand)
{
	git_reference *ref;

	cl_git_pass(git_reference_lookup(&ref, repo, refname));
	cl_assert_equal_s(git_reference_shorthand(ref), shorthand);
	git_reference_free(ref);
}