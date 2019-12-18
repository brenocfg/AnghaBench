#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct tm {int dummy; } ;
struct stat {int /*<<< orphan*/  st_mode; } ;
struct dirent {scalar_t__ d_type; char* d_name; size_t d_namlen; } ;
struct TYPE_2__ {int /*<<< orphan*/  suffix; } ;

/* Variables and functions */
 int /*<<< orphan*/  AT_SYMLINK_NOFOLLOW ; 
 int COMPRESS_TYPES ; 
 scalar_t__ DT_REG ; 
 scalar_t__ DT_UNKNOWN ; 
 int /*<<< orphan*/  S_ISREG (int /*<<< orphan*/ ) ; 
 TYPE_1__* compress_type ; 
 scalar_t__ fstatat (int,char*,struct stat*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct tm*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  printf (char*,char*,...) ; 
 scalar_t__ strcmp (char*,int /*<<< orphan*/ ) ; 
 size_t strlen (char const*) ; 
 scalar_t__ strncmp (char*,char const*,size_t) ; 
 char* strptime (char*,int /*<<< orphan*/ ,struct tm*) ; 
 int /*<<< orphan*/  timefnamefmt ; 
 scalar_t__ verbose ; 

__attribute__((used)) static int
validate_old_timelog(int fd, const struct dirent *dp, const char *logfname,
    struct tm *tm)
{
	struct stat sb;
	size_t logfname_len;
	char *s;
	int c;

	logfname_len = strlen(logfname);

	if (dp->d_type != DT_REG) {
		/*
		 * Some filesystems (e.g. NFS) don't fill out the d_type field
		 * and leave it set to DT_UNKNOWN; in this case we must obtain
		 * the file type ourselves.
		 */
		if (dp->d_type != DT_UNKNOWN ||
		    fstatat(fd, dp->d_name, &sb, AT_SYMLINK_NOFOLLOW) != 0 ||
		    !S_ISREG(sb.st_mode))
			return (0);
	}
	/* Ignore everything but files with our logfile prefix. */
	if (strncmp(dp->d_name, logfname, logfname_len) != 0)
		return (0);
	/* Ignore the actual non-rotated logfile. */
	if (dp->d_namlen == logfname_len)
		return (0);

	/*
	 * Make sure we created have found a logfile, so the
	 * postfix is valid, IE format is: '.<time>(.[bgx]z)?'.
	 */
	if (dp->d_name[logfname_len] != '.') {
		if (verbose)
			printf("Ignoring %s which has unexpected "
			    "extension '%s'\n", dp->d_name,
			    &dp->d_name[logfname_len]);
		return (0);
	}
	memset(tm, 0, sizeof(*tm));
	if ((s = strptime(&dp->d_name[logfname_len + 1],
	    timefnamefmt, tm)) == NULL) {
		/*
		 * We could special case "old" sequentially named logfiles here,
		 * but we do not as that would require special handling to
		 * decide which one was the oldest compared to "new" time based
		 * logfiles.
		 */
		if (verbose)
			printf("Ignoring %s which does not "
			    "match time format\n", dp->d_name);
		return (0);
	}

	for (c = 0; c < COMPRESS_TYPES; c++)
		if (strcmp(s, compress_type[c].suffix) == 0)
			/* We're done. */
			return (1);

	if (verbose)
		printf("Ignoring %s which has unexpected extension '%s'\n",
		    dp->d_name, s);

	return (0);
}