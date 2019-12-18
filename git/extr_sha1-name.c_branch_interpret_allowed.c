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
 unsigned int INTERPRET_BRANCH_LOCAL ; 
 unsigned int INTERPRET_BRANCH_REMOTE ; 
 scalar_t__ starts_with (char const*,char*) ; 

__attribute__((used)) static int branch_interpret_allowed(const char *refname, unsigned allowed)
{
	if (!allowed)
		return 1;

	if ((allowed & INTERPRET_BRANCH_LOCAL) &&
	    starts_with(refname, "refs/heads/"))
		return 1;
	if ((allowed & INTERPRET_BRANCH_REMOTE) &&
	    starts_with(refname, "refs/remotes/"))
		return 1;

	return 0;
}