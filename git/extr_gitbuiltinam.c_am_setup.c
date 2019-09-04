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
struct strbuf {char* buf; } ;
struct object_id {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  argv; } ;
struct am_state {int threeway; int quiet; int signoff; int utf8; scalar_t__ allow_rerere_autoupdate; int keep; int message_id; int scissors; int /*<<< orphan*/  last; int /*<<< orphan*/  cur; scalar_t__ rebasing; TYPE_1__ git_apply_opts; int /*<<< orphan*/  dir; } ;
typedef  enum patch_format { ____Placeholder_patch_format } patch_format ;

/* Variables and functions */
 int /*<<< orphan*/  BUG (char*) ; 
 scalar_t__ EEXIST ; 
#define  KEEP_FALSE 133 
#define  KEEP_NON_PATCH 132 
#define  KEEP_TRUE 131 
 int /*<<< orphan*/  REF_NO_DEREF ; 
 scalar_t__ RERERE_AUTOUPDATE ; 
#define  SCISSORS_FALSE 130 
#define  SCISSORS_TRUE 129 
#define  SCISSORS_UNSET 128 
 struct strbuf STRBUF_INIT ; 
 int /*<<< orphan*/  UPDATE_REFS_DIE_ON_ERR ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  am_destroy (struct am_state*) ; 
 int /*<<< orphan*/  delete_ref (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int detect_patch_format (char const**) ; 
 int /*<<< orphan*/  die (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  die_errno (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fprintf_ln (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_oid (char*,struct object_id*) ; 
 scalar_t__ mkdir (int /*<<< orphan*/ ,int) ; 
 char* oid_to_hex (struct object_id*) ; 
 scalar_t__ split_mail (struct am_state*,int,char const**,int) ; 
 int /*<<< orphan*/  sq_quote_argv (struct strbuf*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  strbuf_release (struct strbuf*) ; 
 int /*<<< orphan*/  update_ref (char*,char*,struct object_id*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write_state_bool (struct am_state*,char*,int) ; 
 int /*<<< orphan*/  write_state_count (struct am_state*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write_state_text (struct am_state*,char*,char const*) ; 

__attribute__((used)) static void am_setup(struct am_state *state, enum patch_format patch_format,
			const char **paths, int keep_cr)
{
	struct object_id curr_head;
	const char *str;
	struct strbuf sb = STRBUF_INIT;

	if (!patch_format)
		patch_format = detect_patch_format(paths);

	if (!patch_format) {
		fprintf_ln(stderr, _("Patch format detection failed."));
		exit(128);
	}

	if (mkdir(state->dir, 0777) < 0 && errno != EEXIST)
		die_errno(_("failed to create directory '%s'"), state->dir);
	delete_ref(NULL, "REBASE_HEAD", NULL, REF_NO_DEREF);

	if (split_mail(state, patch_format, paths, keep_cr) < 0) {
		am_destroy(state);
		die(_("Failed to split patches."));
	}

	if (state->rebasing)
		state->threeway = 1;

	write_state_bool(state, "threeway", state->threeway);
	write_state_bool(state, "quiet", state->quiet);
	write_state_bool(state, "sign", state->signoff);
	write_state_bool(state, "utf8", state->utf8);

	if (state->allow_rerere_autoupdate)
		write_state_bool(state, "rerere-autoupdate",
			 state->allow_rerere_autoupdate == RERERE_AUTOUPDATE);

	switch (state->keep) {
	case KEEP_FALSE:
		str = "f";
		break;
	case KEEP_TRUE:
		str = "t";
		break;
	case KEEP_NON_PATCH:
		str = "b";
		break;
	default:
		BUG("invalid value for state->keep");
	}

	write_state_text(state, "keep", str);
	write_state_bool(state, "messageid", state->message_id);

	switch (state->scissors) {
	case SCISSORS_UNSET:
		str = "";
		break;
	case SCISSORS_FALSE:
		str = "f";
		break;
	case SCISSORS_TRUE:
		str = "t";
		break;
	default:
		BUG("invalid value for state->scissors");
	}
	write_state_text(state, "scissors", str);

	sq_quote_argv(&sb, state->git_apply_opts.argv);
	write_state_text(state, "apply-opt", sb.buf);

	if (state->rebasing)
		write_state_text(state, "rebasing", "");
	else
		write_state_text(state, "applying", "");

	if (!get_oid("HEAD", &curr_head)) {
		write_state_text(state, "abort-safety", oid_to_hex(&curr_head));
		if (!state->rebasing)
			update_ref("am", "ORIG_HEAD", &curr_head, NULL, 0,
				   UPDATE_REFS_DIE_ON_ERR);
	} else {
		write_state_text(state, "abort-safety", "");
		if (!state->rebasing)
			delete_ref(NULL, "ORIG_HEAD", NULL, 0);
	}

	/*
	 * NOTE: Since the "next" and "last" files determine if an am_state
	 * session is in progress, they should be written last.
	 */

	write_state_count(state, "next", state->cur);
	write_state_count(state, "last", state->last);

	strbuf_release(&sb);
}