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
 scalar_t__ check_filename (char const*,char const*) ; 
 int /*<<< orphan*/  die (int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  die_verify_filename (int /*<<< orphan*/ ,char const*,char const*,int) ; 
 scalar_t__ looks_like_pathspec (char const*) ; 
 int /*<<< orphan*/  the_repository ; 

void verify_filename(const char *prefix,
		     const char *arg,
		     int diagnose_misspelt_rev)
{
	if (*arg == '-')
		die(_("option '%s' must come before non-option arguments"), arg);
	if (looks_like_pathspec(arg) || check_filename(prefix, arg))
		return;
	die_verify_filename(the_repository, prefix, arg, diagnose_misspelt_rev);
}