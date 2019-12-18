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
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int BUFSIZ ; 
 scalar_t__ CONFIGVERS ; 
 scalar_t__ MAJOR_VERS (scalar_t__) ; 
 scalar_t__ atoi (char*) ; 
 int /*<<< orphan*/  badversion () ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 scalar_t__ fgets (char*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * open_makefile_template () ; 
 scalar_t__ strncmp (char*,char*,int) ; 
 scalar_t__ versreq ; 

__attribute__((used)) static void
checkversion(void)
{
	FILE *ifp;
	char line[BUFSIZ];

	ifp = open_makefile_template();
	while (fgets(line, BUFSIZ, ifp) != 0) {
		if (*line != '%')
			continue;
		if (strncmp(line, "%VERSREQ=", 9) != 0)
			continue;
		versreq = atoi(line + 9);
		if (MAJOR_VERS(versreq) == MAJOR_VERS(CONFIGVERS) &&
		    versreq <= CONFIGVERS)
			continue;
		badversion();
	}
	fclose(ifp);
}