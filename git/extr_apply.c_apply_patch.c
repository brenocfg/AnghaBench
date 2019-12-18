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
struct strbuf {size_t len; scalar_t__ buf; } ;
struct patch {int inaccurate_eof; int recount; scalar_t__ old_name; scalar_t__ new_name; struct patch* next; } ;
struct apply_state {char const* patch_input_file; scalar_t__ apply_verbosity; scalar_t__ ws_error_action; int update_index; int /*<<< orphan*/  fn_table; scalar_t__ summary; scalar_t__ numstat; scalar_t__ diffstat; scalar_t__ fake_ancestor; scalar_t__ apply_with_reject; scalar_t__ apply; scalar_t__ check; scalar_t__ check_index; int /*<<< orphan*/  lock_file; int /*<<< orphan*/  repo; scalar_t__ index_file; scalar_t__ ita_only; scalar_t__ whitespace_error; scalar_t__ apply_in_reverse; } ;

/* Variables and functions */
 int APPLY_OPT_INACCURATE_EOF ; 
 int APPLY_OPT_RECOUNT ; 
 int /*<<< orphan*/  GITATTRIBUTES_FILE ; 
 int /*<<< orphan*/  LOCK_DIE_ON_ERROR ; 
 struct strbuf STRBUF_INIT ; 
 int /*<<< orphan*/  _ (char*) ; 
 scalar_t__ build_fake_ancestor (struct apply_state*,struct patch*) ; 
 int check_patch_list (struct apply_state*,struct patch*) ; 
 scalar_t__ die_on_ws_error ; 
 scalar_t__ ends_with_path_components (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  error (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_patch (struct patch*) ; 
 int /*<<< orphan*/  free_patch_list (struct patch*) ; 
 int /*<<< orphan*/  hold_lock_file_for_update (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  is_lock_file_locked (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  numstat_patch_list (struct apply_state*,struct patch*) ; 
 int parse_chunk (struct apply_state*,scalar_t__,size_t,struct patch*) ; 
 int /*<<< orphan*/  patch_stats (struct apply_state*,struct patch*) ; 
 scalar_t__ read_apply_cache (struct apply_state*) ; 
 scalar_t__ read_patch_file (struct strbuf*,int) ; 
 int /*<<< orphan*/  repo_hold_locked_index (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  reset_parsed_attributes () ; 
 int /*<<< orphan*/  reverse_patches (struct patch*) ; 
 int /*<<< orphan*/  say_patch_name (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct patch*) ; 
 int /*<<< orphan*/  stat_patch_list (struct apply_state*,struct patch*) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  strbuf_release (struct strbuf*) ; 
 int /*<<< orphan*/  string_list_clear (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  summary_patch_list (struct patch*) ; 
 scalar_t__ use_patch (struct apply_state*,struct patch*) ; 
 scalar_t__ verbosity_normal ; 
 scalar_t__ verbosity_silent ; 
 int write_out_results (struct apply_state*,struct patch*) ; 
 struct patch* xcalloc (int,int) ; 

__attribute__((used)) static int apply_patch(struct apply_state *state,
		       int fd,
		       const char *filename,
		       int options)
{
	size_t offset;
	struct strbuf buf = STRBUF_INIT; /* owns the patch text */
	struct patch *list = NULL, **listp = &list;
	int skipped_patch = 0;
	int res = 0;
	int flush_attributes = 0;

	state->patch_input_file = filename;
	if (read_patch_file(&buf, fd) < 0)
		return -128;
	offset = 0;
	while (offset < buf.len) {
		struct patch *patch;
		int nr;

		patch = xcalloc(1, sizeof(*patch));
		patch->inaccurate_eof = !!(options & APPLY_OPT_INACCURATE_EOF);
		patch->recount =  !!(options & APPLY_OPT_RECOUNT);
		nr = parse_chunk(state, buf.buf + offset, buf.len - offset, patch);
		if (nr < 0) {
			free_patch(patch);
			if (nr == -128) {
				res = -128;
				goto end;
			}
			break;
		}
		if (state->apply_in_reverse)
			reverse_patches(patch);
		if (use_patch(state, patch)) {
			patch_stats(state, patch);
			*listp = patch;
			listp = &patch->next;

			if ((patch->new_name &&
			     ends_with_path_components(patch->new_name,
						       GITATTRIBUTES_FILE)) ||
			    (patch->old_name &&
			     ends_with_path_components(patch->old_name,
						       GITATTRIBUTES_FILE)))
				flush_attributes = 1;
		}
		else {
			if (state->apply_verbosity > verbosity_normal)
				say_patch_name(stderr, _("Skipped patch '%s'."), patch);
			free_patch(patch);
			skipped_patch++;
		}
		offset += nr;
	}

	if (!list && !skipped_patch) {
		error(_("unrecognized input"));
		res = -128;
		goto end;
	}

	if (state->whitespace_error && (state->ws_error_action == die_on_ws_error))
		state->apply = 0;

	state->update_index = (state->check_index || state->ita_only) && state->apply;
	if (state->update_index && !is_lock_file_locked(&state->lock_file)) {
		if (state->index_file)
			hold_lock_file_for_update(&state->lock_file,
						  state->index_file,
						  LOCK_DIE_ON_ERROR);
		else
			repo_hold_locked_index(state->repo, &state->lock_file,
					       LOCK_DIE_ON_ERROR);
	}

	if (state->check_index && read_apply_cache(state) < 0) {
		error(_("unable to read index file"));
		res = -128;
		goto end;
	}

	if (state->check || state->apply) {
		int r = check_patch_list(state, list);
		if (r == -128) {
			res = -128;
			goto end;
		}
		if (r < 0 && !state->apply_with_reject) {
			res = -1;
			goto end;
		}
	}

	if (state->apply) {
		int write_res = write_out_results(state, list);
		if (write_res < 0) {
			res = -128;
			goto end;
		}
		if (write_res > 0) {
			/* with --3way, we still need to write the index out */
			res = state->apply_with_reject ? -1 : 1;
			goto end;
		}
	}

	if (state->fake_ancestor &&
	    build_fake_ancestor(state, list)) {
		res = -128;
		goto end;
	}

	if (state->diffstat && state->apply_verbosity > verbosity_silent)
		stat_patch_list(state, list);

	if (state->numstat && state->apply_verbosity > verbosity_silent)
		numstat_patch_list(state, list);

	if (state->summary && state->apply_verbosity > verbosity_silent)
		summary_patch_list(list);

	if (flush_attributes)
		reset_parsed_attributes();
end:
	free_patch_list(list);
	strbuf_release(&buf);
	string_list_clear(&state->fn_table, 0);
	return res;
}