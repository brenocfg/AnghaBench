#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  git_attr_file_source ;
struct TYPE_2__ {int /*<<< orphan*/  files; int /*<<< orphan*/  attr_session; int /*<<< orphan*/  repo; int /*<<< orphan*/ * index; int /*<<< orphan*/ * workdir; int /*<<< orphan*/  flags; } ;
typedef  TYPE_1__ attr_walk_up_info ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_ATTR_FILE ; 
 int attr_decide_sources (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int push_attr_file (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int push_one_attr(void *ref, const char *path)
{
	int error = 0, n_src, i;
	attr_walk_up_info *info = (attr_walk_up_info *)ref;
	git_attr_file_source src[2];

	n_src = attr_decide_sources(
		info->flags, info->workdir != NULL, info->index != NULL, src);

	for (i = 0; !error && i < n_src; ++i)
		error = push_attr_file(info->repo, info->attr_session,
			info->files, src[i], path, GIT_ATTR_FILE);

	return error;
}