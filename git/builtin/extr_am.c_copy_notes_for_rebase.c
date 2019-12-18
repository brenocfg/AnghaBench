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
struct strbuf {int len; int /*<<< orphan*/  buf; } ;
struct object_id {int dummy; } ;
struct notes_rewrite_cfg {int dummy; } ;
struct am_state {int /*<<< orphan*/  rebasing; } ;
struct TYPE_2__ {int hexsz; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 struct strbuf STRBUF_INIT ; 
 char* _ (char*) ; 
 int /*<<< orphan*/  am_path (struct am_state const*,char*) ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 scalar_t__ copy_note_for_rewrite (struct notes_rewrite_cfg*,struct object_id*,struct object_id*) ; 
 int error (char const*,char*,...) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  finish_copy_notes_for_rewrite (int /*<<< orphan*/ ,struct notes_rewrite_cfg*,char const*) ; 
 scalar_t__ get_oid_hex (char const*,struct object_id*) ; 
 struct notes_rewrite_cfg* init_copy_notes_for_rewrite (char*) ; 
 char* oid_to_hex (struct object_id*) ; 
 scalar_t__ parse_oid_hex (int /*<<< orphan*/ ,struct object_id*,char const**) ; 
 int /*<<< orphan*/  strbuf_getline_lf (struct strbuf*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strbuf_release (struct strbuf*) ; 
 TYPE_1__* the_hash_algo ; 
 int /*<<< orphan*/  the_repository ; 
 int /*<<< orphan*/ * xfopen (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int copy_notes_for_rebase(const struct am_state *state)
{
	struct notes_rewrite_cfg *c;
	struct strbuf sb = STRBUF_INIT;
	const char *invalid_line = _("Malformed input line: '%s'.");
	const char *msg = "Notes added by 'git rebase'";
	FILE *fp;
	int ret = 0;

	assert(state->rebasing);

	c = init_copy_notes_for_rewrite("rebase");
	if (!c)
		return 0;

	fp = xfopen(am_path(state, "rewritten"), "r");

	while (!strbuf_getline_lf(&sb, fp)) {
		struct object_id from_obj, to_obj;
		const char *p;

		if (sb.len != the_hash_algo->hexsz * 2 + 1) {
			ret = error(invalid_line, sb.buf);
			goto finish;
		}

		if (parse_oid_hex(sb.buf, &from_obj, &p)) {
			ret = error(invalid_line, sb.buf);
			goto finish;
		}

		if (*p != ' ') {
			ret = error(invalid_line, sb.buf);
			goto finish;
		}

		if (get_oid_hex(p + 1, &to_obj)) {
			ret = error(invalid_line, sb.buf);
			goto finish;
		}

		if (copy_note_for_rewrite(c, &from_obj, &to_obj))
			ret = error(_("Failed to copy notes from '%s' to '%s'"),
					oid_to_hex(&from_obj), oid_to_hex(&to_obj));
	}

finish:
	finish_copy_notes_for_rewrite(the_repository, c, msg);
	fclose(fp);
	strbuf_release(&sb);
	return ret;
}