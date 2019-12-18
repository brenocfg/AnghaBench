#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct stat {int /*<<< orphan*/  st_mtime; } ;
struct dirent {char* d_name; } ;
struct TYPE_10__ {TYPE_1__* gp; } ;
struct TYPE_9__ {char* progname; } ;
typedef  TYPE_2__ SCR ;
typedef  int /*<<< orphan*/  FILE ;
typedef  int /*<<< orphan*/  DIR ;

/* Variables and functions */
 scalar_t__ ENOENT ; 
#define  LOCK_FAILED 130 
#define  LOCK_SUCCESS 129 
#define  LOCK_UNAVAIL 128 
 int /*<<< orphan*/  M_ERR ; 
 int /*<<< orphan*/  M_SYSERR ; 
 int /*<<< orphan*/  O_RECDIR ; 
 char* O_STR (TYPE_2__*,int /*<<< orphan*/ ) ; 
 scalar_t__ chdir (char*) ; 
 int /*<<< orphan*/  closedir (int /*<<< orphan*/ *) ; 
 char* ctime (int /*<<< orphan*/ *) ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int file_lock (TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  fileno (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char*,char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  fstat (int /*<<< orphan*/ ,struct stat*) ; 
 int /*<<< orphan*/  msgq_str (TYPE_2__*,int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/ * opendir (char*) ; 
 scalar_t__ opts_empty (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,char*,...) ; 
 int rcv_dlnread (TYPE_2__*,char**,char**,int /*<<< orphan*/ *) ; 
 struct dirent* readdir (int /*<<< orphan*/ *) ; 
 scalar_t__ stat (char*,struct stat*) ; 
 int /*<<< orphan*/  strcmp (char*,char*) ; 
 scalar_t__ strncmp (char*,char*,int) ; 
 int /*<<< orphan*/  unlink (char*) ; 

int
rcv_list(SCR *sp)
{
	struct dirent *dp;
	struct stat sb;
	DIR *dirp;
	FILE *fp;
	int found;
	char *p, *file, *path;
	char *dtype, *data;
	int st;

	/* Open the recovery directory for reading. */
	if (opts_empty(sp, O_RECDIR, 0))
		return (1);
	p = O_STR(sp, O_RECDIR);
	if (chdir(p) || (dirp = opendir(".")) == NULL) {
		msgq_str(sp, M_SYSERR, p, "recdir: %s");
		return (1);
	}

	/* Read the directory. */
	for (found = 0; (dp = readdir(dirp)) != NULL;) {
		if (strncmp(dp->d_name, "recover.", 8))
			continue;

		/* If it's readable, it's recoverable. */
		if ((fp = fopen(dp->d_name, "r")) == NULL)
			continue;

		switch (file_lock(sp, NULL, fileno(fp), 1)) {
		case LOCK_FAILED:
			/*
			 * XXX
			 * Assume that a lock can't be acquired, but that we
			 * should permit recovery anyway.  If this is wrong,
			 * and someone else is using the file, we're going to
			 * die horribly.
			 */
			break;
		case LOCK_SUCCESS:
			break;
		case LOCK_UNAVAIL:
			/* If it's locked, it's live. */
			(void)fclose(fp);
			continue;
		}

		/* Check the headers. */
		for (file = NULL, path = NULL;
		    file == NULL || path == NULL;) {
			if ((st = rcv_dlnread(sp, &dtype, &data, fp))) {
				if (st == 1)
					msgq_str(sp, M_ERR, dp->d_name,
					    "066|%s: malformed recovery file");
				goto next;
			}
			if (dtype == NULL)
				continue;
			if (!strcmp(dtype, "file"))
				file = data;
			else if (!strcmp(dtype, "path"))
				path = data;
			else
				free(data);
		}

		/*
		 * If the file doesn't exist, it's an orphaned recovery file,
		 * toss it.
		 *
		 * XXX
		 * This can occur if the backup file was deleted and we crashed
		 * before deleting the email file.
		 */
		errno = 0;
		if (stat(path, &sb) &&
		    errno == ENOENT) {
			(void)unlink(dp->d_name);
			goto next;
		}

		/* Get the last modification time and display. */
		(void)fstat(fileno(fp), &sb);
		(void)printf("%.24s: %s\n",
		    ctime(&sb.st_mtime), file);
		found = 1;

		/* Close, discarding lock. */
next:		(void)fclose(fp);
		if (file != NULL)
			free(file);
		if (path != NULL)
			free(path);
	}
	if (found == 0)
		(void)printf("%s: No files to recover\n", sp->gp->progname);
	(void)closedir(dirp);
	return (0);
}