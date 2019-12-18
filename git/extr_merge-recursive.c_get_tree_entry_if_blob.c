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
struct repository {int dummy; } ;
struct object_id {int dummy; } ;
struct diff_filespec {scalar_t__ mode; int /*<<< orphan*/  oid; } ;

/* Variables and functions */
 scalar_t__ S_ISDIR (scalar_t__) ; 
 int get_tree_entry (struct repository*,struct object_id const*,char const*,int /*<<< orphan*/ *,scalar_t__*) ; 
 int /*<<< orphan*/  null_oid ; 
 int /*<<< orphan*/  oidcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int get_tree_entry_if_blob(struct repository *r,
				  const struct object_id *tree,
				  const char *path,
				  struct diff_filespec *dfs)
{
	int ret;

	ret = get_tree_entry(r, tree, path, &dfs->oid, &dfs->mode);
	if (S_ISDIR(dfs->mode)) {
		oidcpy(&dfs->oid, &null_oid);
		dfs->mode = 0;
	}
	return ret;
}