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
struct mtablist {int /*<<< orphan*/  mtab_host; int /*<<< orphan*/  mtab_dirp; struct mtablist* mtab_next; } ;

/* Variables and functions */
 int /*<<< orphan*/  MNTNAMLEN ; 
 int /*<<< orphan*/  bzero (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (char*) ; 
 struct mtablist* mtabhead ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char*) ; 
 char* strdup (char*) ; 
 int /*<<< orphan*/  warnx (char*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
clean_mtab(char *hostp, char *dirp, int verbose)
{
	struct mtablist *mtabp;
	char *host;

	/* Copy hostp in case it points to an entry that we are zeroing out. */
	host = strdup(hostp);
	for (mtabp = mtabhead; mtabp != NULL; mtabp = mtabp->mtab_next) {
		if (strcmp(mtabp->mtab_host, host) != 0)
			continue;
		if (dirp != NULL && strcmp(mtabp->mtab_dirp, dirp) != 0)
			continue;

		if (verbose)
			warnx("delete mounttab entry%s %s:%s",
			    (dirp == NULL) ? " by host" : "",
			    mtabp->mtab_host, mtabp->mtab_dirp);
		bzero(mtabp->mtab_host, MNTNAMLEN);
	}
	free(host);
}