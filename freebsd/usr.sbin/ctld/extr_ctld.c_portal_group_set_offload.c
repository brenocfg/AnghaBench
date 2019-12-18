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
struct portal_group {int /*<<< orphan*/ * pg_offload; int /*<<< orphan*/  pg_name; } ;

/* Variables and functions */
 int /*<<< orphan*/ * checked_strdup (char const*) ; 
 int /*<<< orphan*/  log_warnx (char*,char const*,int /*<<< orphan*/ ) ; 

int
portal_group_set_offload(struct portal_group *pg, const char *offload)
{

	if (pg->pg_offload != NULL) {
		log_warnx("cannot set offload to \"%s\" for "
		    "portal-group \"%s\"; already defined",
		    offload, pg->pg_name);
		return (1);
	}

	pg->pg_offload = checked_strdup(offload);

	return (0);
}