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
struct strbuf {int /*<<< orphan*/  buf; } ;
struct repository {int dummy; } ;
struct object_id {int dummy; } ;
struct diff_options {int dummy; } ;
struct commit_list {struct commit* item; } ;
struct commit {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEFAULT_ABBREV ; 
 unsigned int DIRTY_SUBMODULE_MODIFIED ; 
 unsigned int DIRTY_SUBMODULE_UNTRACKED ; 
 struct strbuf STRBUF_INIT ; 
 int /*<<< orphan*/  diff_emit_submodule_header (struct diff_options*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  diff_emit_submodule_modified (struct diff_options*,char const*) ; 
 int /*<<< orphan*/  diff_emit_submodule_untracked (struct diff_options*,char const*) ; 
 scalar_t__ is_null_oid (struct object_id*) ; 
 struct commit* lookup_commit_reference (struct repository*,struct object_id*) ; 
 scalar_t__ oideq (struct object_id*,struct object_id*) ; 
 struct commit_list* repo_get_merge_bases (struct repository*,struct commit*,struct commit*) ; 
 int /*<<< orphan*/  strbuf_add_unique_abbrev (struct strbuf*,struct object_id*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strbuf_addf (struct strbuf*,char*,char const*) ; 
 int /*<<< orphan*/  strbuf_addstr (struct strbuf*,char*) ; 
 int /*<<< orphan*/  strbuf_release (struct strbuf*) ; 

__attribute__((used)) static void show_submodule_header(struct diff_options *o,
		const char *path,
		struct object_id *one, struct object_id *two,
		unsigned dirty_submodule,
		struct repository *sub,
		struct commit **left, struct commit **right,
		struct commit_list **merge_bases)
{
	const char *message = NULL;
	struct strbuf sb = STRBUF_INIT;
	int fast_forward = 0, fast_backward = 0;

	if (dirty_submodule & DIRTY_SUBMODULE_UNTRACKED)
		diff_emit_submodule_untracked(o, path);

	if (dirty_submodule & DIRTY_SUBMODULE_MODIFIED)
		diff_emit_submodule_modified(o, path);

	if (is_null_oid(one))
		message = "(new submodule)";
	else if (is_null_oid(two))
		message = "(submodule deleted)";

	if (!sub) {
		if (!message)
			message = "(commits not present)";
		goto output_header;
	}

	/*
	 * Attempt to lookup the commit references, and determine if this is
	 * a fast forward or fast backwards update.
	 */
	*left = lookup_commit_reference(sub, one);
	*right = lookup_commit_reference(sub, two);

	/*
	 * Warn about missing commits in the submodule project, but only if
	 * they aren't null.
	 */
	if ((!is_null_oid(one) && !*left) ||
	     (!is_null_oid(two) && !*right))
		message = "(commits not present)";

	*merge_bases = repo_get_merge_bases(sub, *left, *right);
	if (*merge_bases) {
		if ((*merge_bases)->item == *left)
			fast_forward = 1;
		else if ((*merge_bases)->item == *right)
			fast_backward = 1;
	}

	if (oideq(one, two)) {
		strbuf_release(&sb);
		return;
	}

output_header:
	strbuf_addf(&sb, "Submodule %s ", path);
	strbuf_add_unique_abbrev(&sb, one, DEFAULT_ABBREV);
	strbuf_addstr(&sb, (fast_backward || fast_forward) ? ".." : "...");
	strbuf_add_unique_abbrev(&sb, two, DEFAULT_ABBREV);
	if (message)
		strbuf_addf(&sb, " %s\n", message);
	else
		strbuf_addf(&sb, "%s:\n", fast_backward ? " (rewind)" : "");
	diff_emit_submodule_header(o, sb.buf);

	strbuf_release(&sb);
}