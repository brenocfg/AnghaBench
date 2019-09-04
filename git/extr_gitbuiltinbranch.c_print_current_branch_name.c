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
 int REF_ISSYMREF ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  die (int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  puts (char const*) ; 
 char* resolve_ref_unsafe (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int*) ; 
 scalar_t__ skip_prefix (char const*,char*,char const**) ; 

__attribute__((used)) static void print_current_branch_name(void)
{
	int flags;
	const char *refname = resolve_ref_unsafe("HEAD", 0, NULL, &flags);
	const char *shortname;
	if (!refname)
		die(_("could not resolve HEAD"));
	else if (!(flags & REF_ISSYMREF))
		return;
	else if (skip_prefix(refname, "refs/heads/", &shortname))
		puts(shortname);
	else
		die(_("HEAD (%s) points outside of refs/heads/"), refname);
}