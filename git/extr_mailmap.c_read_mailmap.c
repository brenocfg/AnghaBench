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
struct string_list {int strdup_strings; int /*<<< orphan*/  cmp; } ;
struct TYPE_2__ {scalar_t__ have_repository; } ;

/* Variables and functions */
 char* git_mailmap_blob ; 
 char* git_mailmap_file ; 
 scalar_t__ is_bare_repository () ; 
 int /*<<< orphan*/  namemap_cmp ; 
 int read_mailmap_blob (struct string_list*,char*,char**) ; 
 int read_mailmap_file (struct string_list*,char*,char**) ; 
 TYPE_1__* startup_info ; 

int read_mailmap(struct string_list *map, char **repo_abbrev)
{
	int err = 0;

	map->strdup_strings = 1;
	map->cmp = namemap_cmp;

	if (!git_mailmap_blob && is_bare_repository())
		git_mailmap_blob = "HEAD:.mailmap";

	err |= read_mailmap_file(map, ".mailmap", repo_abbrev);
	if (startup_info->have_repository)
		err |= read_mailmap_blob(map, git_mailmap_blob, repo_abbrev);
	err |= read_mailmap_file(map, git_mailmap_file, repo_abbrev);
	return err;
}