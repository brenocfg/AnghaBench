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
typedef  scalar_t__ u_long ;
typedef  scalar_t__ time_t ;
struct mtablist {char* mtab_host; char* mtab_dirp; struct mtablist* mtab_next; scalar_t__ mtab_time; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 scalar_t__ ENOENT ; 
 int /*<<< orphan*/  LOG_ERR ; 
 int MNTNAMLEN ; 
 int MNTPATHLEN ; 
 int /*<<< orphan*/  PATH_MOUNTTAB ; 
 int STRSIZ ; 
 scalar_t__ ULONG_MAX ; 
 int /*<<< orphan*/  badline (char*,char*) ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fgets (char*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (int /*<<< orphan*/ ,char*) ; 
 struct mtablist* malloc (int) ; 
 int /*<<< orphan*/  memmove (char*,char*,int) ; 
 struct mtablist* mtabhead ; 
 char* strsep (char**,char*) ; 
 scalar_t__ strtoul (char*,char**,int) ; 
 int /*<<< orphan*/  syslog (int /*<<< orphan*/ ,char*,...) ; 

int
read_mtab(void)
{
	struct mtablist **mtabpp, *mtabp;
	char *hostp, *dirp, *cp;
	char str[STRSIZ];
	char *timep, *endp;
	time_t actiontime;
	u_long ultmp;
	FILE *mtabfile;

	if ((mtabfile = fopen(PATH_MOUNTTAB, "r")) == NULL) {
		if (errno == ENOENT)
			return (0);
		else {
			syslog(LOG_ERR, "can't open %s", PATH_MOUNTTAB);
			return (0);
		}
	}
	actiontime = 0;
	mtabpp = &mtabhead;
	while (fgets(str, STRSIZ, mtabfile) != NULL) {
		cp = str;
		errno = 0;
		if (*cp == '#' || *cp == ' ' || *cp == '\n')
			continue;
		timep = strsep(&cp, " \t\n");
		if (timep == NULL || *timep == '\0') {
			badline("time", timep);
			continue;
		}
		hostp = strsep(&cp, " \t\n");
		if (hostp == NULL || *hostp == '\0') {
			badline("host", hostp);
			continue;
		}
		dirp = strsep(&cp, " \t\n");
		if (dirp == NULL || *dirp == '\0') {
			badline("dir", dirp);
			continue;
		}
		ultmp = strtoul(timep, &endp, 10);
		if (ultmp == ULONG_MAX || *endp != '\0') {
			badline("time", timep);
			continue;
		}
		actiontime = ultmp;
		if ((mtabp = malloc(sizeof (struct mtablist))) == NULL) {
			syslog(LOG_ERR, "malloc");
			fclose(mtabfile);
			return (0);
		}
		mtabp->mtab_time = actiontime;
		memmove(mtabp->mtab_host, hostp, MNTNAMLEN);
		mtabp->mtab_host[MNTNAMLEN - 1] = '\0';
		memmove(mtabp->mtab_dirp, dirp, MNTPATHLEN);
		mtabp->mtab_dirp[MNTPATHLEN - 1] = '\0';
		mtabp->mtab_next = (struct mtablist *)NULL;
		*mtabpp = mtabp;
		mtabpp = &mtabp->mtab_next;
	}
	fclose(mtabfile);
	return (1);
}