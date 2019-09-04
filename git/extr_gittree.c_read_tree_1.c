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
struct tree_desc {int dummy; } ;
struct tree {int /*<<< orphan*/  size; int /*<<< orphan*/  buffer; } ;
struct strbuf {int len; int /*<<< orphan*/  buf; } ;
struct repository {int /*<<< orphan*/  index; } ;
struct pathspec {int dummy; } ;
struct object_id {int dummy; } ;
struct name_entry {int /*<<< orphan*/  path; int /*<<< orphan*/  oid; int /*<<< orphan*/  mode; } ;
struct commit {int dummy; } ;
typedef  int (* read_tree_fn_t ) (int /*<<< orphan*/ *,struct strbuf*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,void*) ;
typedef  enum interesting { ____Placeholder_interesting } interesting ;

/* Variables and functions */
#define  READ_TREE_RECURSIVE 128 
 scalar_t__ S_ISDIR (int /*<<< orphan*/ ) ; 
 scalar_t__ S_ISGITLINK (int /*<<< orphan*/ ) ; 
 int all_entries_interesting ; 
 int all_entries_not_interesting ; 
 int /*<<< orphan*/  die (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int entry_not_interesting ; 
 int /*<<< orphan*/ * get_commit_tree_oid (struct commit*) ; 
 int /*<<< orphan*/  init_tree_desc (struct tree_desc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct commit* lookup_commit (struct repository*,int /*<<< orphan*/ *) ; 
 struct tree* lookup_tree (struct repository*,struct object_id*) ; 
 int /*<<< orphan*/  oid_to_hex (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  oidcpy (struct object_id*,int /*<<< orphan*/ *) ; 
 scalar_t__ parse_commit (struct commit*) ; 
 scalar_t__ parse_tree (struct tree*) ; 
 int /*<<< orphan*/  strbuf_add (struct strbuf*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  strbuf_addch (struct strbuf*,char) ; 
 int /*<<< orphan*/  strbuf_setlen (struct strbuf*,int) ; 
 scalar_t__ tree_entry (struct tree_desc*,struct name_entry*) ; 
 int tree_entry_interesting (int /*<<< orphan*/ ,struct name_entry*,struct strbuf*,int /*<<< orphan*/ ,struct pathspec const*) ; 
 int tree_entry_len (struct name_entry*) ; 

__attribute__((used)) static int read_tree_1(struct repository *r,
		       struct tree *tree, struct strbuf *base,
		       int stage, const struct pathspec *pathspec,
		       read_tree_fn_t fn, void *context)
{
	struct tree_desc desc;
	struct name_entry entry;
	struct object_id oid;
	int len, oldlen = base->len;
	enum interesting retval = entry_not_interesting;

	if (parse_tree(tree))
		return -1;

	init_tree_desc(&desc, tree->buffer, tree->size);

	while (tree_entry(&desc, &entry)) {
		if (retval != all_entries_interesting) {
			retval = tree_entry_interesting(r->index, &entry,
							base, 0, pathspec);
			if (retval == all_entries_not_interesting)
				break;
			if (retval == entry_not_interesting)
				continue;
		}

		switch (fn(&entry.oid, base,
			   entry.path, entry.mode, stage, context)) {
		case 0:
			continue;
		case READ_TREE_RECURSIVE:
			break;
		default:
			return -1;
		}

		if (S_ISDIR(entry.mode))
			oidcpy(&oid, &entry.oid);
		else if (S_ISGITLINK(entry.mode)) {
			struct commit *commit;

			commit = lookup_commit(r, &entry.oid);
			if (!commit)
				die("Commit %s in submodule path %s%s not found",
				    oid_to_hex(&entry.oid),
				    base->buf, entry.path);

			if (parse_commit(commit))
				die("Invalid commit %s in submodule path %s%s",
				    oid_to_hex(&entry.oid),
				    base->buf, entry.path);

			oidcpy(&oid, get_commit_tree_oid(commit));
		}
		else
			continue;

		len = tree_entry_len(&entry);
		strbuf_add(base, entry.path, len);
		strbuf_addch(base, '/');
		retval = read_tree_1(r, lookup_tree(r, &oid),
				     base, stage, pathspec,
				     fn, context);
		strbuf_setlen(base, oldlen);
		if (retval)
			return -1;
	}
	return 0;
}