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
struct mountlist {char* ml_host; char* ml_dirp; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 scalar_t__ ENOENT ; 
 int /*<<< orphan*/  LOG_ERR ; 
 size_t MNTNAMLEN ; 
 size_t MNTPATHLEN ; 
 int /*<<< orphan*/  SLIST_INSERT_HEAD (int /*<<< orphan*/ *,struct mountlist*,int /*<<< orphan*/ ) ; 
 int STRSIZ ; 
 int /*<<< orphan*/  _PATH_RMOUNTLIST ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fgets (char*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ malloc (int) ; 
 int /*<<< orphan*/  mlhead ; 
 int /*<<< orphan*/  next ; 
 int /*<<< orphan*/  out_of_mem () ; 
 int /*<<< orphan*/  strncpy (char*,char*,size_t) ; 
 char* strsep (char**,char*) ; 
 int /*<<< orphan*/  syslog (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
get_mountlist(void)
{
	struct mountlist *mlp;
	char *host, *dirp, *cp;
	char str[STRSIZ];
	FILE *mlfile;

	if ((mlfile = fopen(_PATH_RMOUNTLIST, "r")) == NULL) {
		if (errno == ENOENT)
			return;
		else {
			syslog(LOG_ERR, "can't open %s", _PATH_RMOUNTLIST);
			return;
		}
	}
	while (fgets(str, STRSIZ, mlfile) != NULL) {
		cp = str;
		host = strsep(&cp, " \t\n");
		dirp = strsep(&cp, " \t\n");
		if (host == NULL || dirp == NULL)
			continue;
		mlp = (struct mountlist *)malloc(sizeof (*mlp));
		if (mlp == (struct mountlist *)NULL)
			out_of_mem();
		strncpy(mlp->ml_host, host, MNTNAMLEN);
		mlp->ml_host[MNTNAMLEN] = '\0';
		strncpy(mlp->ml_dirp, dirp, MNTPATHLEN);
		mlp->ml_dirp[MNTPATHLEN] = '\0';

		SLIST_INSERT_HEAD(&mlhead, mlp, next);
	}
	fclose(mlfile);
}