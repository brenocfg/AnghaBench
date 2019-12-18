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
struct TYPE_2__ {int /*<<< orphan*/  taglist; int /*<<< orphan*/ * pattern; } ;
typedef  TYPE_1__ tag_filter_data ;
typedef  int /*<<< orphan*/  git_oid ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_ERROR_CHECK_ALLOC (char*) ; 
 int GIT_REFS_TAGS_DIR_LEN ; 
 int /*<<< orphan*/  GIT_UNUSED (int /*<<< orphan*/ *) ; 
 char* git__strdup (char const*) ; 
 int git_vector_insert (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ wildmatch (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int tag_list_cb(const char *tag_name, git_oid *oid, void *data)
{
	tag_filter_data *filter = (tag_filter_data *)data;
	GIT_UNUSED(oid);

	if (!*filter->pattern ||
	    wildmatch(filter->pattern, tag_name + GIT_REFS_TAGS_DIR_LEN, 0) == 0)
	{
		char *matched = git__strdup(tag_name + GIT_REFS_TAGS_DIR_LEN);
		GIT_ERROR_CHECK_ALLOC(matched);

		return git_vector_insert(filter->taglist, matched);
	}

	return 0;
}