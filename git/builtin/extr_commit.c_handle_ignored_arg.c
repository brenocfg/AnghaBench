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
struct wt_status {int /*<<< orphan*/  show_ignored_mode; } ;

/* Variables and functions */
 int /*<<< orphan*/  SHOW_MATCHING_IGNORED ; 
 int /*<<< orphan*/  SHOW_NO_IGNORED ; 
 int /*<<< orphan*/  SHOW_TRADITIONAL_IGNORED ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  die (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ignored_arg ; 
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void handle_ignored_arg(struct wt_status *s)
{
	if (!ignored_arg)
		; /* default already initialized */
	else if (!strcmp(ignored_arg, "traditional"))
		s->show_ignored_mode = SHOW_TRADITIONAL_IGNORED;
	else if (!strcmp(ignored_arg, "no"))
		s->show_ignored_mode = SHOW_NO_IGNORED;
	else if (!strcmp(ignored_arg, "matching"))
		s->show_ignored_mode = SHOW_MATCHING_IGNORED;
	else
		die(_("Invalid ignored mode '%s'"), ignored_arg);
}