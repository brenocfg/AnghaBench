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
struct stat {int /*<<< orphan*/  st_mode; } ;
typedef  int ssize_t ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 scalar_t__ S_ISDIR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  add_pattern (char*,size_t) ; 
 int /*<<< orphan*/  err (int,char*,char const*) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 scalar_t__ ferror (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fileno (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char const*,char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 int fstat (int /*<<< orphan*/ ,struct stat*) ; 
 int getline (char**,size_t*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * stdin ; 
 scalar_t__ strcmp (char const*,char*) ; 

__attribute__((used)) static void
read_patterns(const char *fn)
{
	struct stat st;
	FILE *f;
	char *line;
	size_t len;
	ssize_t rlen;

	if (strcmp(fn, "-") == 0)
		f = stdin;
	else if ((f = fopen(fn, "r")) == NULL)
		err(2, "%s", fn);
	if ((fstat(fileno(f), &st) == -1) || (S_ISDIR(st.st_mode))) {
		fclose(f);
		return;
	}
	len = 0;
	line = NULL;
	while ((rlen = getline(&line, &len, f)) != -1) {
		if (line[0] == '\0')
			continue;
		add_pattern(line, line[0] == '\n' ? 0 : (size_t)rlen);
	}

	free(line);
	if (ferror(f))
		err(2, "%s", fn);
	if (strcmp(fn, "-") != 0)
		fclose(f);
}