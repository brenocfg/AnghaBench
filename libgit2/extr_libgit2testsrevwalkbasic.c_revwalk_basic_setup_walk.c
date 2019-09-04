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

/* Variables and functions */
 char const* _fixture ; 
 int /*<<< orphan*/  _repo ; 
 int /*<<< orphan*/  _walk ; 
 int /*<<< orphan*/  cl_fixture (char*) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_git_sandbox_init (char const*) ; 
 int /*<<< orphan*/  git_repository_open (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_revwalk_new (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void revwalk_basic_setup_walk(const char *fixture)
{
	if (fixture) {
		_fixture = fixture;
		_repo = cl_git_sandbox_init(fixture);
	} else {
		cl_git_pass(git_repository_open(&_repo, cl_fixture("testrepo.git")));
	}

	cl_git_pass(git_revwalk_new(&_walk, _repo));
}