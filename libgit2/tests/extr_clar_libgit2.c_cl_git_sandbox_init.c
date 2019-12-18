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
 int /*<<< orphan*/  F_OK ; 
 int /*<<< orphan*/ * _cl_repo ; 
 char const* _cl_sandbox ; 
 char* cl_fixture_basename (char const*) ; 
 int /*<<< orphan*/  cl_fixture_sandbox (char const*) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_rename (char*,char*) ; 
 int /*<<< orphan*/  git_repository_open (int /*<<< orphan*/ **,char const*) ; 
 int /*<<< orphan*/  git_repository_reinit_filesystem (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ p_access (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  p_chdir (char const*) ; 

git_repository *cl_git_sandbox_init(const char *sandbox)
{
	/* Get the name of the sandbox folder which will be created */
	const char *basename = cl_fixture_basename(sandbox);

	/* Copy the whole sandbox folder from our fixtures to our test sandbox
	 * area.  After this it can be accessed with `./sandbox`
	 */
	cl_fixture_sandbox(sandbox);
	_cl_sandbox = sandbox;

	cl_git_pass(p_chdir(basename));

	/* If this is not a bare repo, then rename `sandbox/.gitted` to
	 * `sandbox/.git` which must be done since we cannot store a folder
	 * named `.git` inside the fixtures folder of our libgit2 repo.
	 */
	if (p_access(".gitted", F_OK) == 0)
		cl_git_pass(cl_rename(".gitted", ".git"));

	/* If we have `gitattributes`, rename to `.gitattributes`.  This may
	 * be necessary if we don't want the attributes to be applied in the
	 * libgit2 repo, but just during testing.
	 */
	if (p_access("gitattributes", F_OK) == 0)
		cl_git_pass(cl_rename("gitattributes", ".gitattributes"));

	/* As with `gitattributes`, we may need `gitignore` just for testing. */
	if (p_access("gitignore", F_OK) == 0)
		cl_git_pass(cl_rename("gitignore", ".gitignore"));

	cl_git_pass(p_chdir(".."));

	/* Now open the sandbox repository and make it available for tests */
	cl_git_pass(git_repository_open(&_cl_repo, basename));

	/* Adjust configs after copying to new filesystem */
	cl_git_pass(git_repository_reinit_filesystem(_cl_repo, 0));

	return _cl_repo;
}