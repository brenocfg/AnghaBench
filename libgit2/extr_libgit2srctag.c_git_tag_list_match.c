#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {char const* pattern; int /*<<< orphan*/ * taglist; } ;
typedef  TYPE_1__ tag_filter_data ;
typedef  int /*<<< orphan*/  git_vector ;
struct TYPE_5__ {char** strings; int /*<<< orphan*/  count; } ;
typedef  TYPE_2__ git_strarray ;
typedef  int /*<<< orphan*/  git_repository ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int git_tag_foreach (int /*<<< orphan*/ *,int /*<<< orphan*/ *,void*) ; 
 scalar_t__ git_vector_detach (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_vector_free (int /*<<< orphan*/ *) ; 
 int git_vector_init (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tag_list_cb ; 

int git_tag_list_match(git_strarray *tag_names, const char *pattern, git_repository *repo)
{
	int error;
	tag_filter_data filter;
	git_vector taglist;

	assert(tag_names && repo && pattern);

	if ((error = git_vector_init(&taglist, 8, NULL)) < 0)
		return error;

	filter.taglist = &taglist;
	filter.pattern = pattern;

	error = git_tag_foreach(repo, &tag_list_cb, (void *)&filter);

	if (error < 0)
		git_vector_free(&taglist);

	tag_names->strings =
		(char **)git_vector_detach(&tag_names->count, NULL, &taglist);

	return 0;
}