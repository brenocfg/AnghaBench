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
 int /*<<< orphan*/ * FORTDIR ; 
 int /*<<< orphan*/ * Fortune_path ; 
 char** Fortune_path_arr ; 
 scalar_t__ calloc (int,int) ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/ * getenv (char*) ; 
 scalar_t__ is_dir (char*) ; 
 int /*<<< orphan*/  stderr ; 
 void* strdup (int /*<<< orphan*/ *) ; 
 char* strtok (char*,char*) ; 

__attribute__((used)) static void
getpath(void)
{
	int	nstr, foundenv;
	char	*pch, **ppch, *str, *path;

	foundenv = 1;
	Fortune_path = getenv("FORTUNE_PATH");
	if (Fortune_path == NULL) {
		Fortune_path = FORTDIR;
		foundenv = 0;
	}
	path = strdup(Fortune_path);

	for (nstr = 2, pch = path; *pch != '\0'; pch++) {
		if (*pch == ':')
			nstr++;
	}

	ppch = Fortune_path_arr = (char **)calloc(nstr, sizeof(char *));
	
	nstr = 0;
	str = strtok(path, ":");
	while (str) {
		if (is_dir(str)) {
			nstr++;
			*ppch++ = str;
		}
		str = strtok(NULL, ":");
	}

	if (nstr == 0) {
		if (foundenv == 1) {
			fprintf(stderr,
			    "fortune: FORTUNE_PATH: None of the specified "
			    "directories found.\n");
			exit(1);
		}
		free(path);
		Fortune_path_arr[0] = strdup(FORTDIR);
	}
}