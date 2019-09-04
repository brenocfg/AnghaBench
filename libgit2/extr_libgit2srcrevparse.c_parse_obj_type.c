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
typedef  int /*<<< orphan*/  git_object_t ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_OBJECT_BLOB ; 
 int /*<<< orphan*/  GIT_OBJECT_COMMIT ; 
 int /*<<< orphan*/  GIT_OBJECT_INVALID ; 
 int /*<<< orphan*/  GIT_OBJECT_TAG ; 
 int /*<<< orphan*/  GIT_OBJECT_TREE ; 
 int /*<<< orphan*/  strcmp (char const*,char*) ; 

__attribute__((used)) static git_object_t parse_obj_type(const char *str)
{
	if (!strcmp(str, "commit"))
		return GIT_OBJECT_COMMIT;

	if (!strcmp(str, "tree"))
		return GIT_OBJECT_TREE;

	if (!strcmp(str, "blob"))
		return GIT_OBJECT_BLOB;

	if (!strcmp(str, "tag"))
		return GIT_OBJECT_TAG;

	return GIT_OBJECT_INVALID;
}