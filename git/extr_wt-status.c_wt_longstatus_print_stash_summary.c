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
struct wt_status {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_COLOR_NORMAL ; 
 int /*<<< orphan*/  Q_ (char*,char*,int) ; 
 int /*<<< orphan*/  for_each_reflog_ent (char*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  stash_count_refs ; 
 int /*<<< orphan*/  status_printf_ln (struct wt_status*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void wt_longstatus_print_stash_summary(struct wt_status *s)
{
	int stash_count = 0;

	for_each_reflog_ent("refs/stash", stash_count_refs, &stash_count);
	if (stash_count > 0)
		status_printf_ln(s, GIT_COLOR_NORMAL,
				 Q_("Your stash currently has %d entry",
				    "Your stash currently has %d entries", stash_count),
				 stash_count);
}