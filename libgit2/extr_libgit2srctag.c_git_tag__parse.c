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
typedef  int /*<<< orphan*/  git_tag ;
typedef  int /*<<< orphan*/  git_odb_object ;

/* Variables and functions */
 char* git_odb_object_data (int /*<<< orphan*/ *) ; 
 int git_odb_object_size (int /*<<< orphan*/ *) ; 
 int tag_parse (int /*<<< orphan*/ *,char const*,char const*) ; 

int git_tag__parse(void *_tag, git_odb_object *odb_obj)
{
	git_tag *tag = _tag;
	const char *buffer = git_odb_object_data(odb_obj);
	const char *buffer_end = buffer + git_odb_object_size(odb_obj);

	return tag_parse(tag, buffer, buffer_end);
}