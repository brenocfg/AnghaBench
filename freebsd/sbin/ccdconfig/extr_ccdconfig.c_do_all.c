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
typedef  int /*<<< orphan*/  line ;
typedef  int /*<<< orphan*/  gid_t ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int CCD_UNCONFIGALL ; 
 int _POSIX2_LINE_MAX ; 
 int /*<<< orphan*/  ccdconf ; 
 scalar_t__ do_single (int,char**,int) ; 
 int /*<<< orphan*/  err (int,char*) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fgets (char*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  free (char**) ; 
 int /*<<< orphan*/  getegid () ; 
 int /*<<< orphan*/  getgid () ; 
 int /*<<< orphan*/  lineno ; 
 char** realloc (char**,int) ; 
 scalar_t__ setegid (int /*<<< orphan*/ ) ; 
 char* strrchr (char*,char) ; 
 char* strtok (char*,char*) ; 
 int /*<<< orphan*/  warn (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  warnx (char*) ; 

__attribute__((used)) static int
do_all(int action)
{
	FILE *f;
	char line[_POSIX2_LINE_MAX];
	char *cp, **argv;
	int argc, rval;
	gid_t egid;

	rval = 0;
	egid = getegid();
	if (setegid(getgid()) != 0)
		err(1, "setegid failed");
	if ((f = fopen(ccdconf, "r")) == NULL) {
		if (setegid(egid) != 0)
			err(1, "setegid failed");
		warn("fopen: %s", ccdconf);
		return (1);
	}
	if (setegid(egid) != 0)
		err(1, "setegid failed");

	while (fgets(line, sizeof(line), f) != NULL) {
		argc = 0;
		argv = NULL;
		++lineno;
		if ((cp = strrchr(line, '\n')) != NULL)
			*cp = '\0';

		/* Break up the line and pass it's contents to do_single(). */
		if (line[0] == '\0')
			goto end_of_line;
		for (cp = line; (cp = strtok(cp, " \t")) != NULL; cp = NULL) {
			if (*cp == '#')
				break;
			if ((argv = realloc(argv,
			    sizeof(char *) * ++argc)) == NULL) {
				warnx("no memory to configure ccds");
				return (1);
			}
			argv[argc - 1] = cp;
			/*
			 * If our action is to unconfigure all, then pass
			 * just the first token to do_single() and ignore
			 * the rest.  Since this will be encountered on
			 * our first pass through the line, the Right
			 * Thing will happen.
			 */
			if (action == CCD_UNCONFIGALL) {
				if (do_single(argc, argv, action))
					rval = 1;
				goto end_of_line;
			}
		}
		if (argc != 0)
			if (do_single(argc, argv, action))
				rval = 1;

 end_of_line:
		if (argv != NULL)
			free(argv);
	}

	(void)fclose(f);
	return (rval);
}