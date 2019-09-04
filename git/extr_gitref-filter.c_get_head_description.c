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
struct wt_status_state {scalar_t__ detached_from; scalar_t__ onto; scalar_t__ branch; scalar_t__ detached_at; scalar_t__ bisect_in_progress; scalar_t__ rebase_interactive_in_progress; scalar_t__ rebase_in_progress; } ;
struct strbuf {int dummy; } ;
typedef  int /*<<< orphan*/  state ;

/* Variables and functions */
 struct strbuf STRBUF_INIT ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  free (scalar_t__) ; 
 int /*<<< orphan*/  memset (struct wt_status_state*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  strbuf_addf (struct strbuf*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  strbuf_addstr (struct strbuf*,int /*<<< orphan*/ ) ; 
 char* strbuf_detach (struct strbuf*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  the_repository ; 
 int /*<<< orphan*/  wt_status_get_state (int /*<<< orphan*/ ,struct wt_status_state*,int) ; 

char *get_head_description(void)
{
	struct strbuf desc = STRBUF_INIT;
	struct wt_status_state state;
	memset(&state, 0, sizeof(state));
	wt_status_get_state(the_repository, &state, 1);
	if (state.rebase_in_progress ||
	    state.rebase_interactive_in_progress) {
		if (state.branch)
			strbuf_addf(&desc, _("(no branch, rebasing %s)"),
				    state.branch);
		else
			strbuf_addf(&desc, _("(no branch, rebasing detached HEAD %s)"),
				    state.detached_from);
	} else if (state.bisect_in_progress)
		strbuf_addf(&desc, _("(no branch, bisect started on %s)"),
			    state.branch);
	else if (state.detached_from) {
		if (state.detached_at)
			/*
			 * TRANSLATORS: make sure this matches "HEAD
			 * detached at " in wt-status.c
			 */
			strbuf_addf(&desc, _("(HEAD detached at %s)"),
				state.detached_from);
		else
			/*
			 * TRANSLATORS: make sure this matches "HEAD
			 * detached from " in wt-status.c
			 */
			strbuf_addf(&desc, _("(HEAD detached from %s)"),
				state.detached_from);
	}
	else
		strbuf_addstr(&desc, _("(no branch)"));
	free(state.branch);
	free(state.onto);
	free(state.detached_from);
	return strbuf_detach(&desc, NULL);
}