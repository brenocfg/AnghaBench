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
struct dirent {char* d_name; scalar_t__ d_type; } ;
typedef  int /*<<< orphan*/  curfile ;
typedef  int /*<<< orphan*/  DIR ;

/* Variables and functions */
 scalar_t__ DT_REG ; 
 scalar_t__ DT_UNKNOWN ; 
 int PATH_MAX ; 
 int /*<<< orphan*/  PJDLOG_ASSERT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PJDLOG_VERIFY (int) ; 
 int /*<<< orphan*/  bzero (char*,size_t) ; 
 int /*<<< orphan*/  pjdlog_debug (int,char*,...) ; 
 struct dirent* readdir (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rewinddir (int /*<<< orphan*/ *) ; 
 scalar_t__ strcmp (char*,char*) ; 
 size_t strlcpy (char*,char*,size_t) ; 
 scalar_t__ trail_type (int /*<<< orphan*/ *,char*) ; 

void
trail_last(DIR *dirfp, char *filename, size_t filenamesize)
{
	char curfile[PATH_MAX];
	struct dirent *dp;

	PJDLOG_ASSERT(dirfp != NULL);

	curfile[0] = '\0';

	rewinddir(dirfp);
	while ((dp = readdir(dirfp)) != NULL) {
		if (dp->d_name[0] < '0' || dp->d_name[0] > '9')
			continue;
		if (dp->d_type == DT_UNKNOWN)
			dp->d_type = trail_type(dirfp, dp->d_name);
		/* We are only interested in regular files, skip the rest. */
		if (dp->d_type != DT_REG)
			continue;
		/* Skip all files "greater" than curfile. */
		if (curfile[0] != '\0' && strcmp(dp->d_name, curfile) < 0)
			continue;
		PJDLOG_VERIFY(strlcpy(curfile, dp->d_name, sizeof(curfile)) <
		    sizeof(curfile));
	}
	if (curfile[0] == '\0') {
		/*
		 * There are no trail files, so we return.
		 */
		pjdlog_debug(1, "No trail files.");
		bzero(filename, filenamesize);
		return;
	}
	PJDLOG_VERIFY(strlcpy(filename, curfile, filenamesize) < filenamesize);
	pjdlog_debug(1, "Found the most recent trail file: \"%s\".", filename);
}