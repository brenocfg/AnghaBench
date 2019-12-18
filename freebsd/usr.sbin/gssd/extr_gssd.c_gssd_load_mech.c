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
typedef  int /*<<< orphan*/  buf ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  _PATH_GSS_MECH ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 scalar_t__ fgets (char*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*,char*,char*) ; 
 char* getprogname () ; 
 scalar_t__ isspace (char) ; 
 scalar_t__ kldload (char*) ; 
 scalar_t__ modfind (char*) ; 
 int /*<<< orphan*/  stderr ; 
 scalar_t__ strcmp (char*,char*) ; 
 char* strsep (char**,char*) ; 

__attribute__((used)) static void
gssd_load_mech(void)
{
	FILE		*fp;
	char		buf[256];
	char		*p;
	char		*name, *oid, *lib, *kobj;

	fp = fopen(_PATH_GSS_MECH, "r");
	if (!fp)
		return;

	while (fgets(buf, sizeof(buf), fp)) {
		if (*buf == '#')
			continue;
		p = buf;
		name = strsep(&p, "\t\n ");
		if (p) while (isspace(*p)) p++;
		oid = strsep(&p, "\t\n ");
		if (p) while (isspace(*p)) p++;
		lib = strsep(&p, "\t\n ");
		if (p) while (isspace(*p)) p++;
		kobj = strsep(&p, "\t\n ");
		if (!name || !oid || !lib || !kobj)
			continue;

		if (strcmp(kobj, "-")) {
			/*
			 * Attempt to load the kernel module if its
			 * not already present.
			 */
			if (modfind(kobj) < 0) {
				if (kldload(kobj) < 0) {
					fprintf(stderr,
			"%s: can't find or load kernel module %s for %s\n",
					    getprogname(), kobj, name);
				}
			}
		}
	}
	fclose(fp);
}