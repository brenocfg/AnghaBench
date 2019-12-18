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

/* Variables and functions */
 int /*<<< orphan*/  GIT_CONFIGMAP_SYMLINKS ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int git_futils_fake_symlink (char const*,char const*) ; 
 int /*<<< orphan*/  git_repository__configmap_lookup (int*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int p_symlink (char const*,char const*) ; 

__attribute__((used)) static int symlink_or_fake(git_repository *repo, const char *a, const char *b)
{
	int symlinks;

	cl_git_pass(git_repository__configmap_lookup(&symlinks, repo, GIT_CONFIGMAP_SYMLINKS));

	if (symlinks)
		return p_symlink(a, b);
	else
		return git_futils_fake_symlink(a, b);
}