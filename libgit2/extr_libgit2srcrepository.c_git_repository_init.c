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
struct TYPE_4__ {int /*<<< orphan*/  flags; } ;
typedef  TYPE_1__ git_repository_init_options ;
typedef  int /*<<< orphan*/  git_repository ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_REPOSITORY_INIT_BARE ; 
 int /*<<< orphan*/  GIT_REPOSITORY_INIT_MKPATH ; 
 TYPE_1__ GIT_REPOSITORY_INIT_OPTIONS_INIT ; 
 int git_repository_init_ext (int /*<<< orphan*/ **,char const*,TYPE_1__*) ; 

int git_repository_init(
	git_repository **repo_out, const char *path, unsigned is_bare)
{
	git_repository_init_options opts = GIT_REPOSITORY_INIT_OPTIONS_INIT;

	opts.flags = GIT_REPOSITORY_INIT_MKPATH; /* don't love this default */
	if (is_bare)
		opts.flags |= GIT_REPOSITORY_INIT_BARE;

	return git_repository_init_ext(repo_out, path, &opts);
}