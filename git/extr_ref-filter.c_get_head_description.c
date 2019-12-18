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
 scalar_t__ HEAD_DETACHED_AT ; 
 scalar_t__ HEAD_DETACHED_FROM ; 
 struct strbuf STRBUF_INIT ; 
 scalar_t__ _ (char*) ; 
 int /*<<< orphan*/  free (scalar_t__) ; 
 int /*<<< orphan*/  memset (struct wt_status_state*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  strbuf_addch (struct strbuf*,char) ; 
 int /*<<< orphan*/  strbuf_addf (struct strbuf*,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  strbuf_addstr (struct strbuf*,scalar_t__) ; 
 char* strbuf_detach (struct strbuf*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  the_repository ; 
 int /*<<< orphan*/  wt_status_get_state (int /*<<< orphan*/ ,struct wt_status_state*,int) ; 

char *get_head_description(void)
{
	struct strbuf desc = STRBUF_INIT;
	struct wt_status_state state;
	memset(&state, 0, sizeof(state));
	wt_status_get_state(the_repository, &state, 1);

	/*
	 * The ( character must be hard-coded and not part of a localizable
	 * string, since the description is used as a sort key and compared
	 * with ref names.
	 */
	strbuf_addch(&desc, '(');
	if (state.rebase_in_progress ||
	    state.rebase_interactive_in_progress) {
		if (state.branch)
			strbuf_addf(&desc, _("no branch, rebasing %s"),
				    state.branch);
		else
			strbuf_addf(&desc, _("no branch, rebasing detached HEAD %s"),
				    state.detached_from);
	} else if (state.bisect_in_progress)
		strbuf_addf(&desc, _("no branch, bisect started on %s"),
			    state.branch);
	else if (state.detached_from) {
		if (state.detached_at)
			strbuf_addstr(&desc, HEAD_DETACHED_AT);
		else
			strbuf_addstr(&desc, HEAD_DETACHED_FROM);
		strbuf_addstr(&desc, state.detached_from);
	}
	else
		strbuf_addstr(&desc, _("no branch"));
	strbuf_addch(&desc, ')');

	free(state.branch);
	free(state.onto);
	free(state.detached_from);
	return strbuf_detach(&desc, NULL);
}