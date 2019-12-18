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

/* Variables and functions */
 int /*<<< orphan*/  GIT_UNUSED (void*) ; 
 int git_remote_create (int /*<<< orphan*/ **,int /*<<< orphan*/ *,char const*,char const*) ; 

__attribute__((used)) static int custom_remote_ssh_with_paths(
	git_remote **out,
	git_repository *repo,
	const char *name,
	const char *url,
	void *payload)
{
	int error;

	GIT_UNUSED(payload);

	if ((error = git_remote_create(out, repo, name, url)) < 0)
		return error;

	return 0;
}