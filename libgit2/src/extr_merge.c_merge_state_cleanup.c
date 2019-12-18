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
 int /*<<< orphan*/  ARRAY_SIZE (char const**) ; 
 char const* GIT_MERGE_HEAD_FILE ; 
 char const* GIT_MERGE_MODE_FILE ; 
 char const* GIT_MERGE_MSG_FILE ; 
 int git_repository__cleanup_files (int /*<<< orphan*/ *,char const**,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int merge_state_cleanup(git_repository *repo)
{
	const char *state_files[] = {
		GIT_MERGE_HEAD_FILE,
		GIT_MERGE_MODE_FILE,
		GIT_MERGE_MSG_FILE,
	};

	return git_repository__cleanup_files(repo, state_files, ARRAY_SIZE(state_files));
}