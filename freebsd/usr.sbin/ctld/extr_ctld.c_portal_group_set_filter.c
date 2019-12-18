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
struct portal_group {int pg_discovery_filter; int /*<<< orphan*/  pg_name; } ;

/* Variables and functions */
 int PG_FILTER_NONE ; 
 int PG_FILTER_PORTAL ; 
 int PG_FILTER_PORTAL_NAME ; 
 int PG_FILTER_PORTAL_NAME_AUTH ; 
 int PG_FILTER_UNKNOWN ; 
 int /*<<< orphan*/  log_warnx (char*,char const*,int /*<<< orphan*/ ) ; 
 scalar_t__ strcmp (char const*,char*) ; 

int
portal_group_set_filter(struct portal_group *pg, const char *str)
{
	int filter;

	if (strcmp(str, "none") == 0) {
		filter = PG_FILTER_NONE;
	} else if (strcmp(str, "portal") == 0) {
		filter = PG_FILTER_PORTAL;
	} else if (strcmp(str, "portal-name") == 0) {
		filter = PG_FILTER_PORTAL_NAME;
	} else if (strcmp(str, "portal-name-auth") == 0) {
		filter = PG_FILTER_PORTAL_NAME_AUTH;
	} else {
		log_warnx("invalid discovery-filter \"%s\" for portal-group "
		    "\"%s\"; valid values are \"none\", \"portal\", "
		    "\"portal-name\", and \"portal-name-auth\"",
		    str, pg->pg_name);
		return (1);
	}

	if (pg->pg_discovery_filter != PG_FILTER_UNKNOWN &&
	    pg->pg_discovery_filter != filter) {
		log_warnx("cannot set discovery-filter to \"%s\" for "
		    "portal-group \"%s\"; already has a different "
		    "value", str, pg->pg_name);
		return (1);
	}

	pg->pg_discovery_filter = filter;

	return (0);
}