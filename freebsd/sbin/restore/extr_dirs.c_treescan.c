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
struct inotab {long t_seekpt; } ;
struct direct {char* d_name; int d_namlen; int /*<<< orphan*/  d_ino; } ;
typedef  int /*<<< orphan*/  locname ;
typedef  int /*<<< orphan*/  ino_t ;

/* Variables and functions */
 scalar_t__ FAIL ; 
 int LEAF ; 
 int MAXPATHLEN ; 
 int NODE ; 
 int /*<<< orphan*/  dirp ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*,...) ; 
 struct inotab* inotablookup (int /*<<< orphan*/ ) ; 
 struct direct* rst_readdir (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rst_seekdir (int /*<<< orphan*/ ,long,long) ; 
 long rst_telldir (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stderr ; 
 scalar_t__ strcmp (char*,char*) ; 
 int /*<<< orphan*/  strlcat (char*,char*,int) ; 
 int /*<<< orphan*/  strlcpy (char*,char*,int) ; 
 int strlen (char*) ; 
 long stub1 (char*,int /*<<< orphan*/ ,int) ; 
 long stub2 (char*,int /*<<< orphan*/ ,int) ; 

void
treescan(char *pname, ino_t ino, long (*todo)(char *, ino_t, int))
{
	struct inotab *itp;
	struct direct *dp;
	int namelen;
	long bpt;
	char locname[MAXPATHLEN];

	itp = inotablookup(ino);
	if (itp == NULL) {
		/*
		 * Pname is name of a simple file or an unchanged directory.
		 */
		(void) (*todo)(pname, ino, LEAF);
		return;
	}
	/*
	 * Pname is a dumped directory name.
	 */
	if ((*todo)(pname, ino, NODE) == FAIL)
		return;
	/*
	 * begin search through the directory
	 * skipping over "." and ".."
	 */
	(void) strlcpy(locname, pname, sizeof(locname));
	(void) strlcat(locname, "/", sizeof(locname));
	namelen = strlen(locname);
	rst_seekdir(dirp, itp->t_seekpt, itp->t_seekpt);
	dp = rst_readdir(dirp); /* "." */
	if (dp != NULL && strcmp(dp->d_name, ".") == 0)
		dp = rst_readdir(dirp); /* ".." */
	else
		fprintf(stderr, "Warning: `.' missing from directory %s\n",
			pname);
	if (dp != NULL && strcmp(dp->d_name, "..") == 0)
		dp = rst_readdir(dirp); /* first real entry */
	else
		fprintf(stderr, "Warning: `..' missing from directory %s\n",
			pname);
	bpt = rst_telldir(dirp);
	/*
	 * a zero inode signals end of directory
	 */
	while (dp != NULL) {
		locname[namelen] = '\0';
		if (namelen + dp->d_namlen >= sizeof(locname)) {
			fprintf(stderr, "%s%s: name exceeds %zu char\n",
			    locname, dp->d_name, sizeof(locname) - 1);
		} else {
			(void)strlcat(locname, dp->d_name, sizeof(locname));
			treescan(locname, dp->d_ino, todo);
			rst_seekdir(dirp, bpt, itp->t_seekpt);
		}
		dp = rst_readdir(dirp);
		bpt = rst_telldir(dirp);
	}
}