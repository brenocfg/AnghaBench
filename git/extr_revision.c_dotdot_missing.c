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
struct rev_info {scalar_t__ ignore_missing; } ;

/* Variables and functions */
 int /*<<< orphan*/  die (char*,char const*) ; 

__attribute__((used)) static int dotdot_missing(const char *arg, char *dotdot,
			  struct rev_info *revs, int symmetric)
{
	if (revs->ignore_missing)
		return 0;
	/* de-munge so we report the full argument */
	*dotdot = '.';
	die(symmetric
	    ? "Invalid symmetric difference expression %s"
	    : "Invalid revision range %s", arg);
}