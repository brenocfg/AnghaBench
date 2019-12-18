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
struct am_state {int threeway; int quiet; int signoff; int utf8; int message_id; int rebasing; int /*<<< orphan*/  git_apply_opts; int /*<<< orphan*/  scissors; int /*<<< orphan*/  keep; scalar_t__ allow_rerere_autoupdate; int /*<<< orphan*/  orig_commit; void* last; void* cur; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG (char*) ; 
 int /*<<< orphan*/  KEEP_FALSE ; 
 int /*<<< orphan*/  KEEP_NON_PATCH ; 
 int /*<<< orphan*/  KEEP_TRUE ; 
 scalar_t__ RERERE_AUTOUPDATE ; 
 scalar_t__ RERERE_NOAUTOUPDATE ; 
 int /*<<< orphan*/  SCISSORS_FALSE ; 
 int /*<<< orphan*/  SCISSORS_TRUE ; 
 int /*<<< orphan*/  SCISSORS_UNSET ; 
 struct strbuf STRBUF_INIT ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  am_path (struct am_state*,char*) ; 
 int /*<<< orphan*/  argv_array_clear (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  die (int /*<<< orphan*/ ,...) ; 
 scalar_t__ file_exists (int /*<<< orphan*/ ) ; 
 scalar_t__ get_oid_hex (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  oidclr (int /*<<< orphan*/ *) ; 
 scalar_t__ read_am_author_script (struct am_state*) ; 
 int /*<<< orphan*/  read_commit_msg (struct am_state*) ; 
 scalar_t__ read_state_file (struct strbuf*,struct am_state*,char*,int) ; 
 scalar_t__ sq_dequote_to_argv_array (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strbuf_release (struct strbuf*) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char*) ; 
 void* strtol (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void am_load(struct am_state *state)
{
	struct strbuf sb = STRBUF_INIT;

	if (read_state_file(&sb, state, "next", 1) < 0)
		BUG("state file 'next' does not exist");
	state->cur = strtol(sb.buf, NULL, 10);

	if (read_state_file(&sb, state, "last", 1) < 0)
		BUG("state file 'last' does not exist");
	state->last = strtol(sb.buf, NULL, 10);

	if (read_am_author_script(state) < 0)
		die(_("could not parse author script"));

	read_commit_msg(state);

	if (read_state_file(&sb, state, "original-commit", 1) < 0)
		oidclr(&state->orig_commit);
	else if (get_oid_hex(sb.buf, &state->orig_commit) < 0)
		die(_("could not parse %s"), am_path(state, "original-commit"));

	read_state_file(&sb, state, "threeway", 1);
	state->threeway = !strcmp(sb.buf, "t");

	read_state_file(&sb, state, "quiet", 1);
	state->quiet = !strcmp(sb.buf, "t");

	read_state_file(&sb, state, "sign", 1);
	state->signoff = !strcmp(sb.buf, "t");

	read_state_file(&sb, state, "utf8", 1);
	state->utf8 = !strcmp(sb.buf, "t");

	if (file_exists(am_path(state, "rerere-autoupdate"))) {
		read_state_file(&sb, state, "rerere-autoupdate", 1);
		state->allow_rerere_autoupdate = strcmp(sb.buf, "t") ?
			RERERE_NOAUTOUPDATE : RERERE_AUTOUPDATE;
	} else {
		state->allow_rerere_autoupdate = 0;
	}

	read_state_file(&sb, state, "keep", 1);
	if (!strcmp(sb.buf, "t"))
		state->keep = KEEP_TRUE;
	else if (!strcmp(sb.buf, "b"))
		state->keep = KEEP_NON_PATCH;
	else
		state->keep = KEEP_FALSE;

	read_state_file(&sb, state, "messageid", 1);
	state->message_id = !strcmp(sb.buf, "t");

	read_state_file(&sb, state, "scissors", 1);
	if (!strcmp(sb.buf, "t"))
		state->scissors = SCISSORS_TRUE;
	else if (!strcmp(sb.buf, "f"))
		state->scissors = SCISSORS_FALSE;
	else
		state->scissors = SCISSORS_UNSET;

	read_state_file(&sb, state, "apply-opt", 1);
	argv_array_clear(&state->git_apply_opts);
	if (sq_dequote_to_argv_array(sb.buf, &state->git_apply_opts) < 0)
		die(_("could not parse %s"), am_path(state, "apply-opt"));

	state->rebasing = !!file_exists(am_path(state, "rebasing"));

	strbuf_release(&sb);
}