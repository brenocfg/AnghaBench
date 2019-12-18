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

/* Variables and functions */
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  check_filename (char const*,char const*) ; 
 int /*<<< orphan*/  die (int /*<<< orphan*/ ,char const*) ; 
 scalar_t__ is_inside_git_dir () ; 
 int /*<<< orphan*/  is_inside_work_tree () ; 

void verify_non_filename(const char *prefix, const char *arg)
{
	if (!is_inside_work_tree() || is_inside_git_dir())
		return;
	if (*arg == '-')
		return; /* flag */
	if (!check_filename(prefix, arg))
		return;
	die(_("ambiguous argument '%s': both revision and filename\n"
	      "Use '--' to separate paths from revisions, like this:\n"
	      "'git <command> [<revision>...] -- [<file>...]'"), arg);
}