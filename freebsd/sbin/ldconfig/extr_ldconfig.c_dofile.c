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
 int MAXPATHLEN ; 
 int dodir (char*,int) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 scalar_t__ fgets (char*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char*,char*) ; 
 scalar_t__ isspace (char) ; 
 int /*<<< orphan*/  warn (char*,char*) ; 
 int /*<<< orphan*/  warnx (char*,char*) ; 

int
dofile(char *fname, int silent)
{
	FILE *hfp;
	char buf[MAXPATHLEN];
	int rval = 0;
	char *cp, *sp;

	if ((hfp = fopen(fname, "r")) == NULL) {
		warn("%s", fname);
		return -1;
	}

	while (fgets(buf, sizeof(buf), hfp)) {
		cp = buf;
		while (isspace(*cp))
			cp++;
		if (*cp == '#' || *cp == '\0')
			continue;
		sp = cp;
		while (!isspace(*cp) && *cp != '\0')
			cp++;

		if (*cp != '\n') {
			*cp = '\0';
			warnx("%s: trailing characters ignored", sp);
		}

		*cp = '\0';

		rval |= dodir(sp, silent);
	}

	(void)fclose(hfp);
	return rval;
}