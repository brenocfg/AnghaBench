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
 int /*<<< orphan*/  UPRINTF (char*,char*) ; 
 int chdir (char*) ; 
 int code ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  free (char*) ; 
 char* globulize (char*) ; 
 char* localcwd ; 
 char* localhome ; 
 int /*<<< orphan*/  ttyout ; 
 int /*<<< orphan*/  updatelocalcwd () ; 
 int /*<<< orphan*/  warn (char*,char*) ; 

void
lcd(int argc, char *argv[])
{
	char *locdir;

	code = -1;
	if (argc == 1) {
		argc++;
		argv[1] = localhome;
	}
	if (argc != 2) {
		UPRINTF("usage: %s [local-directory]\n", argv[0]);
		return;
	}
	if ((locdir = globulize(argv[1])) == NULL)
		return;
	if (chdir(locdir) == -1)
		warn("Can't chdir `%s'", locdir);
	else {
		updatelocalcwd();
		if (localcwd[0]) {
			fprintf(ttyout, "Local directory now: %s\n", localcwd);
			code = 0;
		} else {
			fprintf(ttyout, "Unable to determine local directory\n");
		}
	}
	(void)free(locdir);
}