#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_8__ ;
typedef  struct TYPE_15__   TYPE_7__ ;
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct strbuf {char* buf; } ;
struct TYPE_9__ {char* buf; } ;
struct TYPE_16__ {int /*<<< orphan*/  argv; } ;
struct rebase_options {int type; int flags; char* gpg_sign_opt; char* state_dir; char* upstream_name; char* head_name; char* onto_name; char* revisions; char* switch_to; char* action; scalar_t__ allow_rerere_autoupdate; char* cmd; char* strategy; char* strategy_opts; scalar_t__ dont_finish_rebase; scalar_t__ autosquash; TYPE_1__ git_format_patch_opt; int /*<<< orphan*/ * squash_onto; scalar_t__ root; scalar_t__ rebase_cousins; scalar_t__ rebase_merges; scalar_t__ allow_empty_message; scalar_t__ keep_empty; scalar_t__ signoff; TYPE_8__ git_am_opts; TYPE_7__* restrict_revision; TYPE_5__* onto; int /*<<< orphan*/  orig_head; TYPE_3__* upstream; } ;
typedef  enum action { ____Placeholder_action } action ;
struct TYPE_14__ {int /*<<< orphan*/  oid; } ;
struct TYPE_15__ {TYPE_6__ object; } ;
struct TYPE_12__ {int /*<<< orphan*/  oid; } ;
struct TYPE_13__ {TYPE_4__ object; } ;
struct TYPE_10__ {int /*<<< orphan*/  oid; } ;
struct TYPE_11__ {TYPE_2__ object; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG (char*,int) ; 
 int REBASE_AM ; 
 int REBASE_DIFFSTAT ; 
 int REBASE_FORCE ; 
 int REBASE_INTERACTIVE ; 
 int REBASE_INTERACTIVE_EXPLICIT ; 
 int REBASE_NO_QUIET ; 
#define  REBASE_PRESERVE_MERGES 128 
 int REBASE_VERBOSE ; 
 scalar_t__ RERERE_AUTOUPDATE ; 
 int /*<<< orphan*/  RUN_USING_SHELL ; 
 struct strbuf STRBUF_INIT ; 
 char* absolute_path (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  add_var (struct strbuf*,char*,char*) ; 
 int /*<<< orphan*/  apply_autostash (struct rebase_options*) ; 
 int /*<<< orphan*/  die (char*) ; 
 int /*<<< orphan*/  file_exists (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  finish_rebase (struct rebase_options*) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  get_git_dir () ; 
 scalar_t__ is_interactive (struct rebase_options*) ; 
 char* oid_to_hex (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  remove_dir_recursively (struct strbuf*,int /*<<< orphan*/ ) ; 
 char* resolvemsg ; 
 int run_am (struct rebase_options*) ; 
 int run_command_v_opt (char const**,int /*<<< orphan*/ ) ; 
 int run_rebase_interactive (struct rebase_options*,int) ; 
 int /*<<< orphan*/  setenv (char*,char*,int) ; 
 int /*<<< orphan*/  sq_quote_argv_pretty (struct strbuf*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  state_dir_path (char*,struct rebase_options*) ; 
 int /*<<< orphan*/  strbuf_addf (struct strbuf*,char*,char const*,char const*) ; 
 int /*<<< orphan*/  strbuf_addstr (struct strbuf*,char*) ; 
 int /*<<< orphan*/  strbuf_release (struct strbuf*) ; 
 char* xstrdup (char*) ; 

__attribute__((used)) static int run_specific_rebase(struct rebase_options *opts, enum action action)
{
	const char *argv[] = { NULL, NULL };
	struct strbuf script_snippet = STRBUF_INIT, buf = STRBUF_INIT;
	int status;
	const char *backend, *backend_func;

	if (opts->type == REBASE_INTERACTIVE) {
		/* Run builtin interactive rebase */
		setenv("GIT_CHERRY_PICK_HELP", resolvemsg, 1);
		if (!(opts->flags & REBASE_INTERACTIVE_EXPLICIT)) {
			setenv("GIT_SEQUENCE_EDITOR", ":", 1);
			opts->autosquash = 0;
		}
		if (opts->gpg_sign_opt) {
			/* remove the leading "-S" */
			char *tmp = xstrdup(opts->gpg_sign_opt + 2);
			free(opts->gpg_sign_opt);
			opts->gpg_sign_opt = tmp;
		}

		status = run_rebase_interactive(opts, action);
		goto finished_rebase;
	}

	if (opts->type == REBASE_AM) {
		status = run_am(opts);
		goto finished_rebase;
	}

	add_var(&script_snippet, "GIT_DIR", absolute_path(get_git_dir()));
	add_var(&script_snippet, "state_dir", opts->state_dir);

	add_var(&script_snippet, "upstream_name", opts->upstream_name);
	add_var(&script_snippet, "upstream", opts->upstream ?
		oid_to_hex(&opts->upstream->object.oid) : NULL);
	add_var(&script_snippet, "head_name",
		opts->head_name ? opts->head_name : "detached HEAD");
	add_var(&script_snippet, "orig_head", oid_to_hex(&opts->orig_head));
	add_var(&script_snippet, "onto", opts->onto ?
		oid_to_hex(&opts->onto->object.oid) : NULL);
	add_var(&script_snippet, "onto_name", opts->onto_name);
	add_var(&script_snippet, "revisions", opts->revisions);
	add_var(&script_snippet, "restrict_revision", opts->restrict_revision ?
		oid_to_hex(&opts->restrict_revision->object.oid) : NULL);
	add_var(&script_snippet, "GIT_QUIET",
		opts->flags & REBASE_NO_QUIET ? "" : "t");
	sq_quote_argv_pretty(&buf, opts->git_am_opts.argv);
	add_var(&script_snippet, "git_am_opt", buf.buf);
	strbuf_release(&buf);
	add_var(&script_snippet, "verbose",
		opts->flags & REBASE_VERBOSE ? "t" : "");
	add_var(&script_snippet, "diffstat",
		opts->flags & REBASE_DIFFSTAT ? "t" : "");
	add_var(&script_snippet, "force_rebase",
		opts->flags & REBASE_FORCE ? "t" : "");
	if (opts->switch_to)
		add_var(&script_snippet, "switch_to", opts->switch_to);
	add_var(&script_snippet, "action", opts->action ? opts->action : "");
	add_var(&script_snippet, "signoff", opts->signoff ? "--signoff" : "");
	add_var(&script_snippet, "allow_rerere_autoupdate",
		opts->allow_rerere_autoupdate ?
			opts->allow_rerere_autoupdate == RERERE_AUTOUPDATE ?
			"--rerere-autoupdate" : "--no-rerere-autoupdate" : "");
	add_var(&script_snippet, "keep_empty", opts->keep_empty ? "yes" : "");
	add_var(&script_snippet, "autosquash", opts->autosquash ? "t" : "");
	add_var(&script_snippet, "gpg_sign_opt", opts->gpg_sign_opt);
	add_var(&script_snippet, "cmd", opts->cmd);
	add_var(&script_snippet, "allow_empty_message",
		opts->allow_empty_message ?  "--allow-empty-message" : "");
	add_var(&script_snippet, "rebase_merges",
		opts->rebase_merges ? "t" : "");
	add_var(&script_snippet, "rebase_cousins",
		opts->rebase_cousins ? "t" : "");
	add_var(&script_snippet, "strategy", opts->strategy);
	add_var(&script_snippet, "strategy_opts", opts->strategy_opts);
	add_var(&script_snippet, "rebase_root", opts->root ? "t" : "");
	add_var(&script_snippet, "squash_onto",
		opts->squash_onto ? oid_to_hex(opts->squash_onto) : "");
	add_var(&script_snippet, "git_format_patch_opt",
		opts->git_format_patch_opt.buf);

	if (is_interactive(opts) &&
	    !(opts->flags & REBASE_INTERACTIVE_EXPLICIT)) {
		strbuf_addstr(&script_snippet,
			      "GIT_SEQUENCE_EDITOR=:; export GIT_SEQUENCE_EDITOR; ");
		opts->autosquash = 0;
	}

	switch (opts->type) {
	case REBASE_PRESERVE_MERGES:
		backend = "git-rebase--preserve-merges";
		backend_func = "git_rebase__preserve_merges";
		break;
	default:
		BUG("Unhandled rebase type %d", opts->type);
		break;
	}

	strbuf_addf(&script_snippet,
		    ". git-sh-setup && . %s && %s", backend, backend_func);
	argv[0] = script_snippet.buf;

	status = run_command_v_opt(argv, RUN_USING_SHELL);
finished_rebase:
	if (opts->dont_finish_rebase)
		; /* do nothing */
	else if (opts->type == REBASE_INTERACTIVE)
		; /* interactive rebase cleans up after itself */
	else if (status == 0) {
		if (!file_exists(state_dir_path("stopped-sha", opts)))
			finish_rebase(opts);
	} else if (status == 2) {
		struct strbuf dir = STRBUF_INIT;

		apply_autostash(opts);
		strbuf_addstr(&dir, opts->state_dir);
		remove_dir_recursively(&dir, 0);
		strbuf_release(&dir);
		die("Nothing to do");
	}

	strbuf_release(&script_snippet);

	return status ? -1 : 0;
}