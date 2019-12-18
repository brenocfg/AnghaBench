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
typedef  int /*<<< orphan*/  zwork ;
typedef  int /*<<< orphan*/  tm ;
typedef  scalar_t__ time_t ;
struct zipwork_entry {int /*<<< orphan*/  zw_fname; int /*<<< orphan*/  zw_fsize; struct conf_entry const* zw_conf; } ;
struct tm {int dummy; } ;
struct stat {int dummy; } ;
struct sigwork_entry {int dummy; } ;
struct conf_entry {int flags; char* log; int numlogs; scalar_t__ compress; int /*<<< orphan*/  fsize; int /*<<< orphan*/ * pid_cmd_file; } ;
typedef  int /*<<< orphan*/  namepart ;
typedef  int /*<<< orphan*/  fk_entry ;
typedef  int /*<<< orphan*/  file2 ;
typedef  int /*<<< orphan*/  file1 ;
typedef  int /*<<< orphan*/  dirpart ;
typedef  int /*<<< orphan*/  datetimestr ;

/* Variables and functions */
 int CE_BINARY ; 
 int CE_PLAIN0 ; 
 scalar_t__ COMPRESS_NONE ; 
 int /*<<< orphan*/  FREE_ENT ; 
 int /*<<< orphan*/  KEEP_ENT ; 
 int MAXPATHLEN ; 
 char* archdirname ; 
 scalar_t__ archtodir ; 
 int /*<<< orphan*/  bzero (struct tm*,int) ; 
 int /*<<< orphan*/  change_attrs (char*,struct conf_entry const*) ; 
 int /*<<< orphan*/  createdir (struct conf_entry const*,char*) ; 
 int /*<<< orphan*/  createlog (struct conf_entry const*) ; 
 int /*<<< orphan*/  delete_classiclog (char*,char*,int) ; 
 int /*<<< orphan*/  delete_oldest_timelog (struct conf_entry const*,char*) ; 
 int /*<<< orphan*/  do_zipwork (struct zipwork_entry*) ; 
 int /*<<< orphan*/  gen_classiclog_fname (char*,int,char*,char*,int) ; 
 char* get_logfile_suffix (char*) ; 
 int /*<<< orphan*/ * localtime_r (scalar_t__*,struct tm*) ; 
 int /*<<< orphan*/  log_trim (char*,struct conf_entry const*) ; 
 scalar_t__ lstat (char*,struct stat*) ; 
 int /*<<< orphan*/  memset (struct zipwork_entry*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ noaction ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  rename (char*,char*) ; 
 struct sigwork_entry* save_sigwork (struct conf_entry const*) ; 
 int /*<<< orphan*/  save_zipwork (struct conf_entry const*,struct sigwork_entry*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  savelog (char*,char*) ; 
 int /*<<< orphan*/  sizefile (char*) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char*,char*,...) ; 
 scalar_t__ strcmp (char*,char*) ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  strftime (char*,int,int /*<<< orphan*/ *,struct tm*) ; 
 int /*<<< orphan*/  strlcat (char*,char const*,int) ; 
 int /*<<< orphan*/  strlcpy (char*,char*,int) ; 
 int strlen (char const*) ; 
 char* strrchr (char*,char) ; 
 scalar_t__ time (scalar_t__*) ; 
 int /*<<< orphan*/ * timefnamefmt ; 
 int /*<<< orphan*/  utimes (char*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static fk_entry
do_rotate(const struct conf_entry *ent)
{
	char dirpart[MAXPATHLEN], namepart[MAXPATHLEN];
	char file1[MAXPATHLEN], file2[MAXPATHLEN];
	char zfile1[MAXPATHLEN], zfile2[MAXPATHLEN];
	const char *logfile_suffix;
	char datetimestr[30];
	int flags, numlogs_c;
	fk_entry free_or_keep;
	struct sigwork_entry *swork;
	struct stat st;
	struct tm tm;
	time_t now;

	flags = ent->flags;
	free_or_keep = FREE_ENT;

	if (archtodir) {
		char *p;

		/* build complete name of archive directory into dirpart */
		if (*archdirname == '/') {	/* absolute */
			strlcpy(dirpart, archdirname, sizeof(dirpart));
		} else {	/* relative */
			/* get directory part of logfile */
			strlcpy(dirpart, ent->log, sizeof(dirpart));
			if ((p = strrchr(dirpart, '/')) == NULL)
				dirpart[0] = '\0';
			else
				*(p + 1) = '\0';
			strlcat(dirpart, archdirname, sizeof(dirpart));
		}

		/* check if archive directory exists, if not, create it */
		if (lstat(dirpart, &st))
			createdir(ent, dirpart);

		/* get filename part of logfile */
		if ((p = strrchr(ent->log, '/')) == NULL)
			strlcpy(namepart, ent->log, sizeof(namepart));
		else
			strlcpy(namepart, p + 1, sizeof(namepart));
	} else {
		/*
		 * Tell utility functions we are not using an archive
		 * dir.
		 */
		dirpart[0] = '\0';
		strlcpy(namepart, ent->log, sizeof(namepart));
	}

	/* Delete old logs */
	if (timefnamefmt != NULL)
		delete_oldest_timelog(ent, dirpart);
	else {
		/*
		 * Handle cleaning up after legacy newsyslog where we
		 * kept ent->numlogs + 1 files.  This code can go away
		 * at some point in the future.
		 */
		delete_classiclog(dirpart, namepart, ent->numlogs);

		if (ent->numlogs > 0)
			delete_classiclog(dirpart, namepart, ent->numlogs - 1);

	}

	if (timefnamefmt != NULL) {
		/* If time functions fails we can't really do any sensible */
		if (time(&now) == (time_t)-1 ||
		    localtime_r(&now, &tm) == NULL)
			bzero(&tm, sizeof(tm));

		strftime(datetimestr, sizeof(datetimestr), timefnamefmt, &tm);
		if (archtodir)
			(void) snprintf(file1, sizeof(file1), "%s/%s.%s",
			    dirpart, namepart, datetimestr);
		else
			(void) snprintf(file1, sizeof(file1), "%s.%s",
			    ent->log, datetimestr);

		/* Don't run the code to move down logs */
		numlogs_c = -1;
	} else {
		gen_classiclog_fname(file1, sizeof(file1), dirpart, namepart,
		    ent->numlogs - 1);
		numlogs_c = ent->numlogs - 2;		/* copy for countdown */
	}

	/* Move down log files */
	for (; numlogs_c >= 0; numlogs_c--) {
		(void) strlcpy(file2, file1, sizeof(file2));

		gen_classiclog_fname(file1, sizeof(file1), dirpart, namepart,
		    numlogs_c);

		logfile_suffix = get_logfile_suffix(file1);
		if (logfile_suffix == NULL)
			continue;
		(void) strlcpy(zfile1, file1, MAXPATHLEN);
		(void) strlcpy(zfile2, file2, MAXPATHLEN);
		(void) strlcat(zfile1, logfile_suffix, MAXPATHLEN);
		(void) strlcat(zfile2, logfile_suffix, MAXPATHLEN);

		if (noaction)
			printf("\tmv %s %s\n", zfile1, zfile2);
		else {
			/* XXX - Ought to be checking for failure! */
			(void)rename(zfile1, zfile2);
			change_attrs(zfile2, ent);
			if (ent->compress && !strlen(logfile_suffix)) {
				/* compress old rotation */
				struct zipwork_entry zwork;

				memset(&zwork, 0, sizeof(zwork));
				zwork.zw_conf = ent;
				zwork.zw_fsize = sizefile(zfile2);
				strcpy(zwork.zw_fname, zfile2);
				do_zipwork(&zwork);
			}
		}
	}

	if (ent->numlogs > 0) {
		if (noaction) {
			/*
			 * Note that savelog() may succeed with using link()
			 * for the archtodir case, but there is no good way
			 * of knowing if it will when doing "noaction", so
			 * here we claim that it will have to do a copy...
			 */
			if (archtodir)
				printf("\tcp %s %s\n", ent->log, file1);
			else
				printf("\tln %s %s\n", ent->log, file1);
			printf("\ttouch %s\t\t"
			    "# Update mtime for 'when'-interval processing\n",
			    file1);
		} else {
			if (!(flags & CE_BINARY)) {
				/* Report the trimming to the old log */
				log_trim(ent->log, ent);
			}
			savelog(ent->log, file1);
			/*
			 * Interval-based rotations are done using the mtime of
			 * the most recently archived log, so make sure it gets
			 * updated during a rotation.
			 */
			utimes(file1, NULL);
		}
		change_attrs(file1, ent);
	}

	/* Create the new log file and move it into place */
	if (noaction)
		printf("Start new log...\n");
	createlog(ent);

	/*
	 * Save all signalling and file-compression to be done after log
	 * files from all entries have been rotated.  This way any one
	 * process will not be sent the same signal multiple times when
	 * multiple log files had to be rotated.
	 */
	swork = NULL;
	if (ent->pid_cmd_file != NULL)
		swork = save_sigwork(ent);
	if (ent->numlogs > 0 && ent->compress > COMPRESS_NONE) {
		if (!(ent->flags & CE_PLAIN0) ||
		    strcmp(&file1[strlen(file1) - 2], ".0") != 0) {
			/*
			 * The zipwork_entry will include a pointer to this
			 * conf_entry, so the conf_entry should not be freed.
			 */
			free_or_keep = KEEP_ENT;
			save_zipwork(ent, swork, ent->fsize, file1);
		}
	}

	return (free_or_keep);
}