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
typedef  int /*<<< orphan*/  path_zoneinfo_file ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int DITEM_FAILURE ; 
 int MAXPATHLEN ; 
 int /*<<< orphan*/  errx (int,char*,char*,char const*) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*,char const*) ; 
 int install_zoneinfo_file (char*) ; 
 int /*<<< orphan*/  path_db ; 
 char* path_zoneinfo ; 
 scalar_t__ reallydoit ; 
 scalar_t__ snprintf (char*,int,char*,char*,char const*) ; 

__attribute__((used)) static int
install_zoneinfo(const char *zoneinfo)
{
	int		rv;
	FILE		*f;
	char		path_zoneinfo_file[MAXPATHLEN];

	if ((size_t)snprintf(path_zoneinfo_file, sizeof(path_zoneinfo_file),
	    "%s/%s", path_zoneinfo, zoneinfo) >= sizeof(path_zoneinfo_file))
		errx(1, "%s/%s name too long", path_zoneinfo, zoneinfo);
	rv = install_zoneinfo_file(path_zoneinfo_file);

	/* Save knowledge for later */
	if (reallydoit && (rv & DITEM_FAILURE) == 0) {
		if ((f = fopen(path_db, "w")) != NULL) {
			fprintf(f, "%s\n", zoneinfo);
			fclose(f);
		}
	}

	return (rv);
}