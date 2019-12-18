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
typedef  int u_int ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  child_set_env (char***,int*,char*,char*) ; 
 int /*<<< orphan*/  fatal (char*,char const*) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char const*,char*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,int,char const*) ; 
 int /*<<< orphan*/  free (char*) ; 
 int getline (char**,size_t*,int /*<<< orphan*/ *) ; 
 int match_pattern_list (char*,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stderr ; 
 char* strchr (char*,char) ; 
 size_t strcspn (char*,char*) ; 

__attribute__((used)) static void
read_environment_file(char ***env, u_int *envsize,
	const char *filename, const char *whitelist)
{
	FILE *f;
	char *line = NULL, *cp, *value;
	size_t linesize = 0;
	u_int lineno = 0;

	f = fopen(filename, "r");
	if (!f)
		return;

	while (getline(&line, &linesize, f) != -1) {
		if (++lineno > 1000)
			fatal("Too many lines in environment file %s", filename);
		for (cp = line; *cp == ' ' || *cp == '\t'; cp++)
			;
		if (!*cp || *cp == '#' || *cp == '\n')
			continue;

		cp[strcspn(cp, "\n")] = '\0';

		value = strchr(cp, '=');
		if (value == NULL) {
			fprintf(stderr, "Bad line %u in %.100s\n", lineno,
			    filename);
			continue;
		}
		/*
		 * Replace the equals sign by nul, and advance value to
		 * the value string.
		 */
		*value = '\0';
		value++;
		if (whitelist != NULL &&
		    match_pattern_list(cp, whitelist, 0) != 1)
			continue;
		child_set_env(env, envsize, cp, value);
	}
	free(line);
	fclose(f);
}