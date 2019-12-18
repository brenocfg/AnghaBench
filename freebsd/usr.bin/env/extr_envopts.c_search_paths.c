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
typedef  int /*<<< orphan*/  candidate ;

/* Variables and functions */
 int /*<<< orphan*/  ENOENT ; 
 int PATH_MAX ; 
 int env_verbosity ; 
 int /*<<< orphan*/  err (int,char*,char*) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*) ; 
 scalar_t__ is_there (char*) ; 
 int snprintf (char*,int,char*,char const*,char*) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/ * strchr (char*,char) ; 
 char* strdup (char*) ; 
 char* strsep (char**,char*) ; 

void
search_paths(char *path, char **argv)
{
        char candidate[PATH_MAX];
        const char *d;
	char *filename, *fqname;

	/* If the file has a `/' in it, then no search is done */
	filename = *argv;
	if (strchr(filename, '/') != NULL)
		return;

	if (env_verbosity > 1) {
		fprintf(stderr, "#env Searching:\t'%s'\n", path);
		fprintf(stderr, "#env  for file:\t'%s'\n", filename);
	}

	fqname = NULL;
        while ((d = strsep(&path, ":")) != NULL) {
                if (*d == '\0')
                        d = ".";
                if (snprintf(candidate, sizeof(candidate), "%s/%s", d,
                    filename) >= (int)sizeof(candidate))
                        continue;
                if (is_there(candidate)) {
                        fqname = candidate;
			break;
                }
        }

	if (fqname == NULL) {
		errno = ENOENT;
		err(127, "%s", filename);
	}
	*argv = strdup(candidate);
}