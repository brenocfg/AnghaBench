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
typedef  int /*<<< orphan*/  gid_t ;

/* Variables and functions */
 int /*<<< orphan*/  _SC_NGROUPS_MAX ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  isspace (unsigned char) ; 
 int /*<<< orphan*/ * malloc (int) ; 
 scalar_t__ setegid (int /*<<< orphan*/ ) ; 
 scalar_t__ setgroups (unsigned int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stderr ; 
 char* strerror (int /*<<< orphan*/ ) ; 
 char* strtok (char*,char*) ; 
 int /*<<< orphan*/  strtol (char*,char**,int /*<<< orphan*/ ) ; 
 long sysconf (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
set_gids(char *gids)
{
	gid_t *gidset;
	long ngroups;
	char *g, *endp;
	unsigned i;

	ngroups = sysconf(_SC_NGROUPS_MAX);
	assert(ngroups > 0);
	gidset = malloc(sizeof(*gidset) * ngroups);
	assert(gidset != NULL);
	for (i = 0, g = strtok(gids, ","); g != NULL;
	    g = strtok(NULL, ","), i++) {
		if ((long)i >= ngroups) {
			fprintf(stderr, "too many gids\n");
			exit(1);
		}
		gidset[i] = strtol(g, &endp, 0);
		if (*endp != '\0' && !isspace((unsigned char)*endp)) {
			fprintf(stderr, "invalid gid '%s' - number expected\n",
			    g);
			exit(1);
		}
	}
	if (setgroups(i, gidset) < 0) {
		fprintf(stderr, "cannot change groups: %s\n", strerror(errno));
		exit(1);
	}
	if (setegid(gidset[0]) < 0) {
		fprintf(stderr, "cannot change effective gid: %s\n",
		    strerror(errno));
		exit(1);
	}
	free(gidset);
}