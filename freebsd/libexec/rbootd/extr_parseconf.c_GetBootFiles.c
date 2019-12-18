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
struct stat {int st_mode; } ;
struct dirent {int /*<<< orphan*/  d_name; } ;
typedef  int /*<<< orphan*/  DIR ;

/* Variables and functions */
 int /*<<< orphan*/  BootDir ; 
 int /*<<< orphan*/ ** BootFiles ; 
 int C_MAXFILE ; 
 int /*<<< orphan*/  FreeStr (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LOG_ERR ; 
 int /*<<< orphan*/ * NewStr (int /*<<< orphan*/ ) ; 
 int S_IFMT ; 
 int S_IFREG ; 
 int /*<<< orphan*/  closedir (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * opendir (char*) ; 
 struct dirent* readdir (int /*<<< orphan*/ *) ; 
 scalar_t__ stat (int /*<<< orphan*/ ,struct stat*) ; 
 int /*<<< orphan*/  syslog (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

int
GetBootFiles(void)
{
	DIR *dfd;
	struct stat statb;
	struct dirent *dp;
	int i;

	/*
	 *  Free the current list of boot files.
	 */
	for (i = 0; i < C_MAXFILE && BootFiles[i] != NULL; i++) {
		FreeStr(BootFiles[i]);
		BootFiles[i] = NULL;
	}

	/*
	 *  Open current directory to read boot file names.
	 */
	if ((dfd = opendir(".")) == NULL) {	/* open BootDir */
		syslog(LOG_ERR, "GetBootFiles: can't open directory (%s)\n",
		       BootDir);
		return(0);
	}

	/*
	 *  Read each boot file name and allocate space for it in the
	 *  list of boot files (BootFiles).  All boot files read after
	 *  C_MAXFILE will be ignored.
	 */
	i = 0;
	for (dp = readdir(dfd); dp != NULL; dp = readdir(dfd)) {
		if (stat(dp->d_name, &statb) < 0 ||
		    (statb.st_mode & S_IFMT) != S_IFREG)
			continue;
		if (i == C_MAXFILE)
			syslog(LOG_ERR,
			       "GetBootFiles: too many boot files (%s ignored)",
			       dp->d_name);
		else if ((BootFiles[i] = NewStr(dp->d_name)) != NULL)
			i++;
	}

	(void) closedir(dfd);			/* close BootDir */

	if (i == 0)				/* can't find any boot files */
		syslog(LOG_ERR, "GetBootFiles: no boot files (%s)\n", BootDir);

	return(i);
}