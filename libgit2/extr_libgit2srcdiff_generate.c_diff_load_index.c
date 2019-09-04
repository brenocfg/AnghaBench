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
typedef  int /*<<< orphan*/  git_index ;

/* Variables and functions */
 int /*<<< orphan*/  git_error_clear () ; 
 scalar_t__ git_index_read (int /*<<< orphan*/ *,int) ; 
 int git_repository_index__weakptr (int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int diff_load_index(git_index **index, git_repository *repo)
{
	int error = git_repository_index__weakptr(index, repo);

	/* reload the repository index when user did not pass one in */
	if (!error && git_index_read(*index, false) < 0)
		git_error_clear();

	return error;
}