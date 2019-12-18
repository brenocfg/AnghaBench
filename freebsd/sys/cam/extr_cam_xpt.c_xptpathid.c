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
typedef  int path_id_t ;
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 int CAM_XPT_PATH_ID ; 
 int /*<<< orphan*/  printf (char*,char const*,int,int,int) ; 
 scalar_t__ resource_find_match (int*,char const**,int*,char*,char*) ; 
 scalar_t__ resource_int_value (char*,int,char*,int*) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char const*,int) ; 
 scalar_t__ strcmp (char const*,char*) ; 
 int xptnextfreepathid () ; 

__attribute__((used)) static path_id_t
xptpathid(const char *sim_name, int sim_unit, int sim_bus)
{
	path_id_t pathid;
	int i, dunit, val;
	char buf[32];
	const char *dname;

	pathid = CAM_XPT_PATH_ID;
	snprintf(buf, sizeof(buf), "%s%d", sim_name, sim_unit);
	if (strcmp(buf, "xpt0") == 0 && sim_bus == 0)
		return (pathid);
	i = 0;
	while ((resource_find_match(&i, &dname, &dunit, "at", buf)) == 0) {
		if (strcmp(dname, "scbus")) {
			/* Avoid a bit of foot shooting. */
			continue;
		}
		if (dunit < 0)		/* unwired?! */
			continue;
		if (resource_int_value("scbus", dunit, "bus", &val) == 0) {
			if (sim_bus == val) {
				pathid = dunit;
				break;
			}
		} else if (sim_bus == 0) {
			/* Unspecified matches bus 0 */
			pathid = dunit;
			break;
		} else {
			printf("Ambiguous scbus configuration for %s%d "
			       "bus %d, cannot wire down.  The kernel "
			       "config entry for scbus%d should "
			       "specify a controller bus.\n"
			       "Scbus will be assigned dynamically.\n",
			       sim_name, sim_unit, sim_bus, dunit);
			break;
		}
	}

	if (pathid == CAM_XPT_PATH_ID)
		pathid = xptnextfreepathid();
	return (pathid);
}