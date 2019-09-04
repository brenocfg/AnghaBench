#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  git_vector ;
struct TYPE_3__ {char* name; } ;
typedef  TYPE_1__ git_config_entry ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_ERROR_CHECK_ALLOC (char*) ; 
 char* git__strndup (char const*,size_t) ; 
 int git_vector_insert (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  strcmp (char const*,char*) ; 
 size_t strlen (char const*) ; 

__attribute__((used)) static int remote_list_cb(const git_config_entry *entry, void *payload)
{
	git_vector *list = payload;
	const char *name = entry->name + strlen("remote.");
	size_t namelen = strlen(name);
	char *remote_name;

	/* we know name matches "remote.<stuff>.(push)?url" */

	if (!strcmp(&name[namelen - 4], ".url"))
		remote_name = git__strndup(name, namelen - 4); /* strip ".url" */
	else
		remote_name = git__strndup(name, namelen - 8); /* strip ".pushurl" */
	GIT_ERROR_CHECK_ALLOC(remote_name);

	return git_vector_insert(list, remote_name);
}