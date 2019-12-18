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
typedef  int ssize_t ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 size_t argc_from_file0 ; 
 char** argv_from_file0 ; 
 int /*<<< orphan*/  closefile (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  err (int,char*,...) ; 
 scalar_t__ ferror (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char const*,char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 int getdelim (char**,size_t*,char,int /*<<< orphan*/ *) ; 
 char** sort_realloc (char**,size_t) ; 

__attribute__((used)) static void
read_fns_from_file0(const char *fn)
{
	FILE *f;
	char *line = NULL;
	size_t linesize = 0;
	ssize_t linelen;

	if (fn == NULL)
		return;

	f = fopen(fn, "r");
	if (f == NULL)
		err(2, "%s", fn);

	while ((linelen = getdelim(&line, &linesize, '\0', f)) != -1) {
		if (*line != '\0') {
			if (argc_from_file0 == (size_t) - 1)
				argc_from_file0 = 0;
			++argc_from_file0;
			argv_from_file0 = sort_realloc(argv_from_file0,
			    argc_from_file0 * sizeof(char *));
			if (argv_from_file0 == NULL)
				err(2, NULL);
			argv_from_file0[argc_from_file0 - 1] = line;
		} else {
			free(line);
		}
		line = NULL;
		linesize = 0;
	}
	if (ferror(f))
		err(2, "%s: getdelim", fn);

	closefile(f, fn);
}