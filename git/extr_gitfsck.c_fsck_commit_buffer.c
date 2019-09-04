#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct object_id {int dummy; } ;
struct fsck_options {int dummy; } ;
struct commit_graft {int nr_parent; } ;
struct TYPE_4__ {int /*<<< orphan*/  oid; } ;
struct commit {TYPE_1__ object; int /*<<< orphan*/  parents; } ;

/* Variables and functions */
 int /*<<< orphan*/  FSCK_MSG_BAD_PARENT_SHA1 ; 
 int /*<<< orphan*/  FSCK_MSG_BAD_TREE ; 
 int /*<<< orphan*/  FSCK_MSG_BAD_TREE_SHA1 ; 
 int /*<<< orphan*/  FSCK_MSG_MISSING_AUTHOR ; 
 int /*<<< orphan*/  FSCK_MSG_MISSING_COMMITTER ; 
 int /*<<< orphan*/  FSCK_MSG_MISSING_GRAFT ; 
 int /*<<< orphan*/  FSCK_MSG_MISSING_PARENT ; 
 int /*<<< orphan*/  FSCK_MSG_MISSING_TREE ; 
 int /*<<< orphan*/  FSCK_MSG_MULTIPLE_AUTHORS ; 
 int /*<<< orphan*/  FSCK_MSG_NUL_IN_COMMIT ; 
 unsigned int commit_list_count (int /*<<< orphan*/ ) ; 
 int fsck_ident (char const**,TYPE_1__*,struct fsck_options*) ; 
 int /*<<< orphan*/  get_commit_tree (struct commit*) ; 
 struct commit_graft* lookup_commit_graft (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ memchr (char const*,char,unsigned long) ; 
 int /*<<< orphan*/  oid_to_hex (struct object_id*) ; 
 scalar_t__ parse_oid_hex (char const*,struct object_id*,char const**) ; 
 int report (struct fsck_options*,TYPE_1__*,int /*<<< orphan*/ ,char*,...) ; 
 scalar_t__ skip_prefix (char const*,char*,char const**) ; 
 int /*<<< orphan*/  the_repository ; 
 scalar_t__ verify_headers (char const*,unsigned long,TYPE_1__*,struct fsck_options*) ; 

__attribute__((used)) static int fsck_commit_buffer(struct commit *commit, const char *buffer,
	unsigned long size, struct fsck_options *options)
{
	struct object_id tree_oid, oid;
	struct commit_graft *graft;
	unsigned parent_count, parent_line_count = 0, author_count;
	int err;
	const char *buffer_begin = buffer;
	const char *p;

	if (verify_headers(buffer, size, &commit->object, options))
		return -1;

	if (!skip_prefix(buffer, "tree ", &buffer))
		return report(options, &commit->object, FSCK_MSG_MISSING_TREE, "invalid format - expected 'tree' line");
	if (parse_oid_hex(buffer, &tree_oid, &p) || *p != '\n') {
		err = report(options, &commit->object, FSCK_MSG_BAD_TREE_SHA1, "invalid 'tree' line format - bad sha1");
		if (err)
			return err;
	}
	buffer = p + 1;
	while (skip_prefix(buffer, "parent ", &buffer)) {
		if (parse_oid_hex(buffer, &oid, &p) || *p != '\n') {
			err = report(options, &commit->object, FSCK_MSG_BAD_PARENT_SHA1, "invalid 'parent' line format - bad sha1");
			if (err)
				return err;
		}
		buffer = p + 1;
		parent_line_count++;
	}
	graft = lookup_commit_graft(the_repository, &commit->object.oid);
	parent_count = commit_list_count(commit->parents);
	if (graft) {
		if (graft->nr_parent == -1 && !parent_count)
			; /* shallow commit */
		else if (graft->nr_parent != parent_count) {
			err = report(options, &commit->object, FSCK_MSG_MISSING_GRAFT, "graft objects missing");
			if (err)
				return err;
		}
	} else {
		if (parent_count != parent_line_count) {
			err = report(options, &commit->object, FSCK_MSG_MISSING_PARENT, "parent objects missing");
			if (err)
				return err;
		}
	}
	author_count = 0;
	while (skip_prefix(buffer, "author ", &buffer)) {
		author_count++;
		err = fsck_ident(&buffer, &commit->object, options);
		if (err)
			return err;
	}
	if (author_count < 1)
		err = report(options, &commit->object, FSCK_MSG_MISSING_AUTHOR, "invalid format - expected 'author' line");
	else if (author_count > 1)
		err = report(options, &commit->object, FSCK_MSG_MULTIPLE_AUTHORS, "invalid format - multiple 'author' lines");
	if (err)
		return err;
	if (!skip_prefix(buffer, "committer ", &buffer))
		return report(options, &commit->object, FSCK_MSG_MISSING_COMMITTER, "invalid format - expected 'committer' line");
	err = fsck_ident(&buffer, &commit->object, options);
	if (err)
		return err;
	if (!get_commit_tree(commit)) {
		err = report(options, &commit->object, FSCK_MSG_BAD_TREE, "could not load commit's tree %s", oid_to_hex(&tree_oid));
		if (err)
			return err;
	}
	if (memchr(buffer_begin, '\0', size)) {
		err = report(options, &commit->object, FSCK_MSG_NUL_IN_COMMIT,
			     "NUL byte in the commit object body");
		if (err)
			return err;
	}
	return 0;
}