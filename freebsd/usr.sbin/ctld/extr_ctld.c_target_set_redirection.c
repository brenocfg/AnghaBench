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
struct target {int /*<<< orphan*/ * t_redirection; int /*<<< orphan*/  t_name; } ;

/* Variables and functions */
 int /*<<< orphan*/ * checked_strdup (char const*) ; 
 int /*<<< orphan*/  log_warnx (char*,char const*,int /*<<< orphan*/ ) ; 

int
target_set_redirection(struct target *target, const char *addr)
{

	if (target->t_redirection != NULL) {
		log_warnx("cannot set redirection to \"%s\" for "
		    "target \"%s\"; already defined",
		    addr, target->t_name);
		return (1);
	}

	target->t_redirection = checked_strdup(addr);

	return (0);
}