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
typedef  int /*<<< orphan*/  new_nd ;
typedef  int /*<<< orphan*/  nd_file ;
typedef  int /*<<< orphan*/  nd ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  LOG_ERR ; 
 int /*<<< orphan*/  LOG_INFO ; 
 int PATH_MAX ; 
 char* SYS_INFINIBAND ; 
 int /*<<< orphan*/  build_node_desc (char*,int,char const*,char const*) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fgets (char*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char*,char*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  newline_to_null (char*) ; 
 int /*<<< orphan*/  rewind (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char*,char*,char const*) ; 
 scalar_t__ strncmp (char*,char*,int) ; 
 char* sys_dir ; 
 int /*<<< orphan*/  syslog (int /*<<< orphan*/ ,char*,char const*,...) ; 

__attribute__((used)) static int update_node_desc(const char *device, const char *hostname, int force)
{
	int rc;
	char nd[128];
	char new_nd[64];
	char nd_file[PATH_MAX];
	FILE *f;

	snprintf(nd_file, sizeof(nd_file), "%s/%s/%s/node_desc",
			sys_dir, SYS_INFINIBAND, device);
	nd_file[sizeof(nd_file)-1] = '\0';

	f = fopen(nd_file, "r+");
	if (!f) {
		syslog(LOG_ERR, "Failed to open %s\n", nd_file);
		return -EIO;
	}

	if (!fgets(nd, sizeof(nd), f)) {
		syslog(LOG_ERR, "Failed to read %s\n", nd_file);
		rc = -EIO;
		goto error;
	}
	newline_to_null(nd);

	build_node_desc(new_nd, sizeof(new_nd), device, hostname);

	if (!force && strncmp(new_nd, nd, sizeof(new_nd)) == 0) {
		syslog(LOG_INFO, "%s: no change (%s)\n", device, new_nd);
	} else {
		syslog(LOG_INFO, "%s: change (%s) -> (%s)\n",
			device, nd, new_nd);
		rewind(f);
		fprintf(f, new_nd);
	}

	rc = 0;
error:
	fclose(f);
	return rc;
}