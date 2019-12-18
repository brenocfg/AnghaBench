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
struct mtablist {char* mtab_host; char* mtab_dirp; scalar_t__ mtab_time; struct mtablist* mtab_next; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  LOG_ERR ; 
 int /*<<< orphan*/  PATH_MOUNTTAB ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*,long,char*,char*) ; 
 struct mtablist* mtabhead ; 
 scalar_t__ strcmp (char*,char*) ; 
 int /*<<< orphan*/  syslog (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int unlink (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  warnx (char*,char*,char*) ; 

int
write_mtab(int verbose)
{
	struct mtablist *mtabp, *mp;
	FILE *mtabfile;
	int line;

	if ((mtabfile = fopen(PATH_MOUNTTAB, "w")) == NULL) {
		syslog(LOG_ERR, "can't write to %s", PATH_MOUNTTAB);
			return (0);
	}
	line = 0;
	for (mtabp = mtabhead; mtabp != NULL; mtabp = mtabp->mtab_next) {
		if (mtabp->mtab_host[0] == '\0')
			continue;
		/* Skip if a later (hence more recent) entry is identical. */
		for (mp = mtabp->mtab_next; mp != NULL; mp = mp->mtab_next)
			if (strcmp(mtabp->mtab_host, mp->mtab_host) == 0 &&
			    strcmp(mtabp->mtab_dirp, mp->mtab_dirp) == 0)
				break;
		if (mp != NULL)
			continue;

		fprintf(mtabfile, "%ld\t%s\t%s\n",
		    (long)mtabp->mtab_time, mtabp->mtab_host,
		    mtabp->mtab_dirp);
		if (verbose)
			warnx("write mounttab entry %s:%s",
			    mtabp->mtab_host, mtabp->mtab_dirp);
		line++;
	}
	fclose(mtabfile);
	if (line == 0) {
		if (unlink(PATH_MOUNTTAB) == -1) {
			syslog(LOG_ERR, "can't remove %s", PATH_MOUNTTAB);
			return (0);
		}
	}
	return (1);
}