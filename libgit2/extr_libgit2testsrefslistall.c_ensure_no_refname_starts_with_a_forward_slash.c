#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {size_t count; int /*<<< orphan*/ * strings; } ;

/* Variables and functions */
 int /*<<< orphan*/  cl_assert (int) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 scalar_t__ git__prefixcmp (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  git_reference_list (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_repository_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_repository_open (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  git_strarray_free (TYPE_1__*) ; 
 TYPE_1__ ref_list ; 
 int /*<<< orphan*/  repo ; 

__attribute__((used)) static void ensure_no_refname_starts_with_a_forward_slash(const char *path)
{
	size_t i;

	cl_git_pass(git_repository_open(&repo, path));
	cl_git_pass(git_reference_list(&ref_list, repo));

	cl_assert(ref_list.count > 0);

	for (i = 0; i < ref_list.count; i++)
		cl_assert(git__prefixcmp(ref_list.strings[i], "/") != 0);

	git_strarray_free(&ref_list);
	git_repository_free(repo);
}