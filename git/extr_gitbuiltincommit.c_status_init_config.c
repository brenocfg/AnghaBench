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
struct wt_status {int /*<<< orphan*/  hints; } ;
typedef  int /*<<< orphan*/  config_fn_t ;

/* Variables and functions */
 int /*<<< orphan*/  advice_status_hints ; 
 int /*<<< orphan*/  determine_whence (struct wt_status*) ; 
 int /*<<< orphan*/  git_config (int /*<<< orphan*/ ,struct wt_status*) ; 
 int /*<<< orphan*/  init_diff_ui_defaults () ; 
 int /*<<< orphan*/  the_repository ; 
 int /*<<< orphan*/  wt_status_prepare (int /*<<< orphan*/ ,struct wt_status*) ; 

__attribute__((used)) static void status_init_config(struct wt_status *s, config_fn_t fn)
{
	wt_status_prepare(the_repository, s);
	init_diff_ui_defaults();
	git_config(fn, s);
	determine_whence(s);
	s->hints = advice_status_hints; /* must come after git_config() */
}