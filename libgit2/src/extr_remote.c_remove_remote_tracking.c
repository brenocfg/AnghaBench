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
typedef  int /*<<< orphan*/  git_remote ;
typedef  int /*<<< orphan*/  git_refspec ;

/* Variables and functions */
 int /*<<< orphan*/  git_remote_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * git_remote_get_refspec (int /*<<< orphan*/ *,size_t) ; 
 int git_remote_lookup (int /*<<< orphan*/ **,int /*<<< orphan*/ *,char const*) ; 
 size_t git_remote_refspec_count (int /*<<< orphan*/ *) ; 
 int remove_refs (int /*<<< orphan*/ *,int /*<<< orphan*/  const*) ; 

__attribute__((used)) static int remove_remote_tracking(git_repository *repo, const char *remote_name)
{
	git_remote *remote;
	int error;
	size_t i, count;

	/* we want to use what's on the config, regardless of changes to the instance in memory */
	if ((error = git_remote_lookup(&remote, repo, remote_name)) < 0)
		return error;

	count = git_remote_refspec_count(remote);
	for (i = 0; i < count; i++) {
		const git_refspec *refspec = git_remote_get_refspec(remote, i);

		/* shouldn't ever actually happen */
		if (refspec == NULL)
			continue;

		if ((error = remove_refs(repo, refspec)) < 0)
			break;
	}

	git_remote_free(remote);
	return error;
}