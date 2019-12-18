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
struct worktree {int dummy; } ;
struct strbuf {int len; char* buf; } ;
struct object_id {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEFAULT_ABBREV ; 
 struct strbuf STRBUF_INIT ; 
 int /*<<< orphan*/  get_oid_hex (char const*,struct object_id*) ; 
 scalar_t__ skip_prefix (char*,char*,char const**) ; 
 scalar_t__ starts_with (char const*,char*) ; 
 int /*<<< orphan*/  strbuf_add_unique_abbrev (struct strbuf*,struct object_id*,int /*<<< orphan*/ ) ; 
 char* strbuf_detach (struct strbuf*,int /*<<< orphan*/ *) ; 
 scalar_t__ strbuf_read_file (struct strbuf*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strbuf_release (struct strbuf*) ; 
 int /*<<< orphan*/  strbuf_remove (struct strbuf*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  strbuf_reset (struct strbuf*) ; 
 int /*<<< orphan*/  strbuf_setlen (struct strbuf*,int) ; 
 int /*<<< orphan*/  strcmp (char const*,char*) ; 
 int /*<<< orphan*/  worktree_git_path (struct worktree const*,char*,char const*) ; 

__attribute__((used)) static char *get_branch(const struct worktree *wt, const char *path)
{
	struct strbuf sb = STRBUF_INIT;
	struct object_id oid;
	const char *branch_name;

	if (strbuf_read_file(&sb, worktree_git_path(wt, "%s", path), 0) <= 0)
		goto got_nothing;

	while (sb.len && sb.buf[sb.len - 1] == '\n')
		strbuf_setlen(&sb, sb.len - 1);
	if (!sb.len)
		goto got_nothing;
	if (skip_prefix(sb.buf, "refs/heads/", &branch_name))
		strbuf_remove(&sb, 0, branch_name - sb.buf);
	else if (starts_with(sb.buf, "refs/"))
		;
	else if (!get_oid_hex(sb.buf, &oid)) {
		strbuf_reset(&sb);
		strbuf_add_unique_abbrev(&sb, &oid, DEFAULT_ABBREV);
	} else if (!strcmp(sb.buf, "detached HEAD")) /* rebase */
		goto got_nothing;
	else			/* bisect */
		;
	return strbuf_detach(&sb, NULL);

got_nothing:
	strbuf_release(&sb);
	return NULL;
}