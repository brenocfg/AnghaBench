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
struct treewalk_skip_data {scalar_t__ stop; scalar_t__ skip; int /*<<< orphan*/  files; int /*<<< orphan*/  dirs; } ;
typedef  int /*<<< orphan*/  git_tree_entry ;

/* Variables and functions */
 scalar_t__ GIT_OBJECT_TREE ; 
 int /*<<< orphan*/  GIT_UNUSED (char const*) ; 
 char* git_tree_entry_name (int /*<<< orphan*/  const*) ; 
 scalar_t__ git_tree_entry_type (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  strcmp (char const*,scalar_t__) ; 

__attribute__((used)) static int treewalk_skip_de_cb(
	const char *root, const git_tree_entry *entry, void *payload)
{
	struct treewalk_skip_data *data = payload;
	const char *name = git_tree_entry_name(entry);

	GIT_UNUSED(root);

	if (git_tree_entry_type(entry) == GIT_OBJECT_TREE)
		data->dirs++;
	else
		data->files++;

	if (data->skip && !strcmp(name, data->skip))
		return 1;
	else if (data->stop && !strcmp(name, data->stop))
		return -1;
	else
		return 0;
}