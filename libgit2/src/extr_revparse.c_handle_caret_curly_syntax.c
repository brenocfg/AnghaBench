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
typedef  scalar_t__ git_object_t ;
typedef  int /*<<< orphan*/  git_object ;

/* Variables and functions */
 int GIT_EINVALIDSPEC ; 
 scalar_t__ GIT_OBJECT_INVALID ; 
 int dereference_to_non_tag (int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_object_id (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_object_owner (int /*<<< orphan*/ *) ; 
 int git_object_peel (int /*<<< orphan*/ **,int /*<<< orphan*/ *,scalar_t__) ; 
 int handle_grep_syntax (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*) ; 
 scalar_t__ parse_obj_type (char const*) ; 

__attribute__((used)) static int handle_caret_curly_syntax(git_object **out, git_object *obj, const char *curly_braces_content)
{
	git_object_t expected_type;

	if (*curly_braces_content == '\0')
		return dereference_to_non_tag(out, obj);

	if (*curly_braces_content == '/')
		return handle_grep_syntax(out, git_object_owner(obj), git_object_id(obj), curly_braces_content + 1);

	expected_type = parse_obj_type(curly_braces_content);

	if (expected_type == GIT_OBJECT_INVALID)
		return GIT_EINVALIDSPEC;

	return git_object_peel(out, obj, expected_type);
}