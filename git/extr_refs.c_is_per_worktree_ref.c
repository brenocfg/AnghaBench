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
 scalar_t__ starts_with (char const*,char*) ; 
 int /*<<< orphan*/  strcmp (char const*,char*) ; 

__attribute__((used)) static int is_per_worktree_ref(const char *refname)
{
	return !strcmp(refname, "HEAD") ||
		starts_with(refname, "refs/worktree/") ||
		starts_with(refname, "refs/bisect/") ||
		starts_with(refname, "refs/rewritten/");
}