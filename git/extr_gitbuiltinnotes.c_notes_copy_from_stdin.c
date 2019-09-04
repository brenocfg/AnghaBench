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
struct strbuf {char* buf; } ;
struct object_id {int dummy; } ;
struct notes_tree {int dummy; } ;
struct notes_rewrite_cfg {int dummy; } ;

/* Variables and functions */
 scalar_t__ EOF ; 
 int /*<<< orphan*/  NOTES_INIT_WRITABLE ; 
 struct strbuf STRBUF_INIT ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  combine_notes_overwrite ; 
 int /*<<< orphan*/  commit_notes (int /*<<< orphan*/ ,struct notes_tree*,char const*) ; 
 int copy_note (struct notes_tree*,struct object_id*,struct object_id*,int,int /*<<< orphan*/ ) ; 
 int copy_note_for_rewrite (struct notes_rewrite_cfg*,struct object_id*,struct object_id*) ; 
 struct notes_tree default_notes_tree ; 
 int /*<<< orphan*/  die (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  error (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  finish_copy_notes_for_rewrite (int /*<<< orphan*/ ,struct notes_rewrite_cfg*,char const*) ; 
 int /*<<< orphan*/  free_notes (struct notes_tree*) ; 
 scalar_t__ get_oid (char*,struct object_id*) ; 
 struct notes_rewrite_cfg* init_copy_notes_for_rewrite (char const*) ; 
 int /*<<< orphan*/  init_notes (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stdin ; 
 scalar_t__ strbuf_getline_lf (struct strbuf*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strbuf_list_free (struct strbuf**) ; 
 int /*<<< orphan*/  strbuf_release (struct strbuf*) ; 
 int /*<<< orphan*/  strbuf_rtrim (struct strbuf*) ; 
 struct strbuf** strbuf_split (struct strbuf*,char) ; 
 int /*<<< orphan*/  the_repository ; 

__attribute__((used)) static int notes_copy_from_stdin(int force, const char *rewrite_cmd)
{
	struct strbuf buf = STRBUF_INIT;
	struct notes_rewrite_cfg *c = NULL;
	struct notes_tree *t = NULL;
	int ret = 0;
	const char *msg = "Notes added by 'git notes copy'";

	if (rewrite_cmd) {
		c = init_copy_notes_for_rewrite(rewrite_cmd);
		if (!c)
			return 0;
	} else {
		init_notes(NULL, NULL, NULL, NOTES_INIT_WRITABLE);
		t = &default_notes_tree;
	}

	while (strbuf_getline_lf(&buf, stdin) != EOF) {
		struct object_id from_obj, to_obj;
		struct strbuf **split;
		int err;

		split = strbuf_split(&buf, ' ');
		if (!split[0] || !split[1])
			die(_("malformed input line: '%s'."), buf.buf);
		strbuf_rtrim(split[0]);
		strbuf_rtrim(split[1]);
		if (get_oid(split[0]->buf, &from_obj))
			die(_("failed to resolve '%s' as a valid ref."), split[0]->buf);
		if (get_oid(split[1]->buf, &to_obj))
			die(_("failed to resolve '%s' as a valid ref."), split[1]->buf);

		if (rewrite_cmd)
			err = copy_note_for_rewrite(c, &from_obj, &to_obj);
		else
			err = copy_note(t, &from_obj, &to_obj, force,
					combine_notes_overwrite);

		if (err) {
			error(_("failed to copy notes from '%s' to '%s'"),
			      split[0]->buf, split[1]->buf);
			ret = 1;
		}

		strbuf_list_free(split);
	}

	if (!rewrite_cmd) {
		commit_notes(the_repository, t, msg);
		free_notes(t);
	} else {
		finish_copy_notes_for_rewrite(the_repository, c, msg);
	}
	strbuf_release(&buf);
	return ret;
}