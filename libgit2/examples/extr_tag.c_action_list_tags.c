#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int /*<<< orphan*/  repo; TYPE_1__* opts; } ;
typedef  TYPE_2__ tag_state ;
struct TYPE_10__ {size_t count; int /*<<< orphan*/ * strings; int /*<<< orphan*/  member_0; } ;
typedef  TYPE_3__ git_strarray ;
struct TYPE_8__ {char* pattern; } ;

/* Variables and functions */
 int /*<<< orphan*/  check_lg2 (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  each_tag (int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  git_strarray_free (TYPE_3__*) ; 
 int /*<<< orphan*/  git_tag_list_match (TYPE_3__*,char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void action_list_tags(tag_state *state)
{
	const char *pattern = state->opts->pattern;
	git_strarray tag_names = {0};
	size_t i;

	check_lg2(git_tag_list_match(&tag_names, pattern ? pattern : "*", state->repo),
			"Unable to get list of tags", NULL);

	for(i = 0; i < tag_names.count; i++) {
		each_tag(tag_names.strings[i], state);
	}

	git_strarray_free(&tag_names);
}