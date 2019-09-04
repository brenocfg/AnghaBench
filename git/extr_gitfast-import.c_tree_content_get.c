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
struct tree_entry {struct tree_content* tree; TYPE_2__* versions; TYPE_1__* name; } ;
struct tree_content {unsigned int entry_count; struct tree_entry** entries; } ;
struct TYPE_4__ {int /*<<< orphan*/  oid; int /*<<< orphan*/  mode; } ;
struct TYPE_3__ {unsigned int str_len; int /*<<< orphan*/  str_dat; } ;

/* Variables and functions */
 int /*<<< orphan*/  S_ISDIR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  die (char*) ; 
 struct tree_content* dup_tree_content (struct tree_content*) ; 
 int /*<<< orphan*/  fspathncmp (char const*,int /*<<< orphan*/ ,unsigned int) ; 
 scalar_t__ is_null_oid (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  load_tree (struct tree_entry*) ; 
 int /*<<< orphan*/  memcpy (struct tree_entry*,struct tree_entry*,int) ; 
 char* strchrnul (char const*,char) ; 

__attribute__((used)) static int tree_content_get(
	struct tree_entry *root,
	const char *p,
	struct tree_entry *leaf,
	int allow_root)
{
	struct tree_content *t;
	const char *slash1;
	unsigned int i, n;
	struct tree_entry *e;

	slash1 = strchrnul(p, '/');
	n = slash1 - p;
	if (!n && !allow_root)
		die("Empty path component found in input");

	if (!root->tree)
		load_tree(root);

	if (!n) {
		e = root;
		goto found_entry;
	}

	t = root->tree;
	for (i = 0; i < t->entry_count; i++) {
		e = t->entries[i];
		if (e->name->str_len == n && !fspathncmp(p, e->name->str_dat, n)) {
			if (!*slash1)
				goto found_entry;
			if (!S_ISDIR(e->versions[1].mode))
				return 0;
			if (!e->tree)
				load_tree(e);
			return tree_content_get(e, slash1 + 1, leaf, 0);
		}
	}
	return 0;

found_entry:
	memcpy(leaf, e, sizeof(*leaf));
	if (e->tree && is_null_oid(&e->versions[1].oid))
		leaf->tree = dup_tree_content(e->tree);
	else
		leaf->tree = NULL;
	return 1;
}