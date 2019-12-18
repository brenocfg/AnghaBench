#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  git_repository ;
typedef  int /*<<< orphan*/  git_remote ;
struct TYPE_5__ {int /*<<< orphan*/  ptr; } ;
typedef  TYPE_1__ git_buf ;

/* Variables and functions */
 TYPE_1__ GIT_BUF_INIT ; 
 int /*<<< orphan*/  git_buf_dispose (TYPE_1__*) ; 
 int git_remote_lookup (int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int lookup_head_remote_key (TYPE_1__*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int lookup_head_remote(git_remote **remote, git_repository *repo)
{
	int error;
	git_buf remote_name = GIT_BUF_INIT;

	/* lookup remote of remote tracking branch name */
	if (!(error = lookup_head_remote_key(&remote_name, repo)))
		error = git_remote_lookup(remote, repo, remote_name.ptr);

	git_buf_dispose(&remote_name);

	return error;
}