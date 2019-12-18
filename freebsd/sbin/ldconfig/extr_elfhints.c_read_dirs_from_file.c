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
 int MAXPATHLEN ; 
 int /*<<< orphan*/  add_dir (char const*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  err (int,char*,char const*) ; 
 int /*<<< orphan*/  errx (int,char*) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fgets (char*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char const*,char*) ; 
 scalar_t__ isspace (char) ; 
 char* strdup (char*) ; 
 int /*<<< orphan*/  warnx (char*,char const*,int) ; 

__attribute__((used)) static void
read_dirs_from_file(const char *hintsfile, const char *listfile)
{
	FILE	*fp;
	char	 buf[MAXPATHLEN];
	int	 linenum;

	if ((fp = fopen(listfile, "r")) == NULL)
		err(1, "%s", listfile);

	linenum = 0;
	while (fgets(buf, sizeof buf, fp) != NULL) {
		char	*cp, *sp;

		linenum++;
		cp = buf;
		/* Skip leading white space. */
		while (isspace(*cp))
			cp++;
		if (*cp == '#' || *cp == '\0')
			continue;
		sp = cp;
		/* Advance over the directory name. */
		while (!isspace(*cp) && *cp != '\0')
			cp++;
		/* Terminate the string and skip trailing white space. */
		if (*cp != '\0') {
			*cp++ = '\0';
			while (isspace(*cp))
				cp++;
		}
		/* Now we had better be at the end of the line. */
		if (*cp != '\0')
			warnx("%s:%d: trailing characters ignored",
			    listfile, linenum);

		if ((sp = strdup(sp)) == NULL)
			errx(1, "Out of memory");
		add_dir(hintsfile, sp, 0);
	}

	fclose(fp);
}