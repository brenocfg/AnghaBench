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
 int /*<<< orphan*/  R_OK ; 
 int access (char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  asprintf (char**,char*,int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  dir ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char const*) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  stderr ; 
 scalar_t__ verbose ; 

__attribute__((used)) static int
check_file(const char *keym)
{
	int status = 0;

	if (access(keym, R_OK) == -1) {
		char *fn;
		asprintf(&fn, "%s/%s", dir, keym);
		if (access(fn, R_OK) == -1) {
			if (verbose)
				fprintf(stderr, "%s not found!\n", fn);
			status = -1;
		}
		free(fn);
	} else {
		if (verbose)
			fprintf(stderr, "No read permission for %s!\n", keym);
		status = -1;
	}

	return status;
}