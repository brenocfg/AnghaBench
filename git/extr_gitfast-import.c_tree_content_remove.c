#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct tree_entry {TYPE_2__* versions; struct tree_content* tree; TYPE_1__* name; } ;
struct tree_content {unsigned int entry_count; struct tree_entry** entries; } ;
struct TYPE_4__ {int /*<<< orphan*/  oid; scalar_t__ mode; } ;
struct TYPE_3__ {unsigned int str_len; int /*<<< orphan*/  str_dat; } ;

/* Variables and functions */
 int /*<<< orphan*/  S_ISDIR (scalar_t__) ; 
 int /*<<< orphan*/  fspathncmp (char const*,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  load_tree (struct tree_entry*) ; 
 int /*<<< orphan*/  memcpy (struct tree_entry*,struct tree_entry*,int) ; 
 int /*<<< orphan*/  oidclr (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  release_tree_content_recursive (struct tree_content*) ; 
 char* strchrnul (char const*,char) ; 

__attribute__((used)) static int tree_content_remove(
	struct tree_entry *root,
	const char *p,
	struct tree_entry *backup_leaf,
	int allow_root)
{
	struct tree_content *t;
	const char *slash1;
	unsigned int i, n;
	struct tree_entry *e;

	slash1 = strchrnul(p, '/');
	n = slash1 - p;

	if (!root->tree)
		load_tree(root);

	if (!*p && allow_root) {
		e = root;
		goto del_entry;
	}

	t = root->tree;
	for (i = 0; i < t->entry_count; i++) {
		e = t->entries[i];
		if (e->name->str_len == n && !fspathncmp(p, e->name->str_dat, n)) {
			if (*slash1 && !S_ISDIR(e->versions[1].mode))
				/*
				 * If p names a file in some subdirectory, and a
				 * file or symlink matching the name of the
				 * parent directory of p exists, then p cannot
				 * exist and need not be deleted.
				 */
				return 1;
			if (!*slash1 || !S_ISDIR(e->versions[1].mode))
				goto del_entry;
			if (!e->tree)
				load_tree(e);
			if (tree_content_remove(e, slash1 + 1, backup_leaf, 0)) {
				for (n = 0; n < e->tree->entry_count; n++) {
					if (e->tree->entries[n]->versions[1].mode) {
						oidclr(&root->versions[1].oid);
						return 1;
					}
				}
				backup_leaf = NULL;
				goto del_entry;
			}
			return 0;
		}
	}
	return 0;

del_entry:
	if (backup_leaf)
		memcpy(backup_leaf, e, sizeof(*backup_leaf));
	else if (e->tree)
		release_tree_content_recursive(e->tree);
	e->tree = NULL;
	e->versions[1].mode = 0;
	oidclr(&e->versions[1].oid);
	oidclr(&root->versions[1].oid);
	return 1;
}