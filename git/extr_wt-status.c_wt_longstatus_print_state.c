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
struct wt_status_state {scalar_t__ bisect_in_progress; scalar_t__ revert_in_progress; scalar_t__ cherry_pick_in_progress; scalar_t__ rebase_interactive_in_progress; scalar_t__ rebase_in_progress; scalar_t__ am_in_progress; scalar_t__ merge_in_progress; } ;
struct wt_status {int /*<<< orphan*/  fp; struct wt_status_state state; } ;

/* Variables and functions */
 int /*<<< orphan*/  WT_STATUS_HEADER ; 
 char* color (int /*<<< orphan*/ ,struct wt_status*) ; 
 int /*<<< orphan*/  fputs (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  show_am_in_progress (struct wt_status*,char const*) ; 
 int /*<<< orphan*/  show_bisect_in_progress (struct wt_status*,char const*) ; 
 int /*<<< orphan*/  show_cherry_pick_in_progress (struct wt_status*,char const*) ; 
 int /*<<< orphan*/  show_merge_in_progress (struct wt_status*,char const*) ; 
 int /*<<< orphan*/  show_rebase_in_progress (struct wt_status*,char const*) ; 
 int /*<<< orphan*/  show_rebase_information (struct wt_status*,char const*) ; 
 int /*<<< orphan*/  show_revert_in_progress (struct wt_status*,char const*) ; 

__attribute__((used)) static void wt_longstatus_print_state(struct wt_status *s)
{
	const char *state_color = color(WT_STATUS_HEADER, s);
	struct wt_status_state *state = &s->state;

	if (state->merge_in_progress) {
		if (state->rebase_interactive_in_progress) {
			show_rebase_information(s, state_color);
			fputs("\n", s->fp);
		}
		show_merge_in_progress(s, state_color);
	} else if (state->am_in_progress)
		show_am_in_progress(s, state_color);
	else if (state->rebase_in_progress || state->rebase_interactive_in_progress)
		show_rebase_in_progress(s, state_color);
	else if (state->cherry_pick_in_progress)
		show_cherry_pick_in_progress(s, state_color);
	else if (state->revert_in_progress)
		show_revert_in_progress(s, state_color);
	if (state->bisect_in_progress)
		show_bisect_in_progress(s, state_color);
}