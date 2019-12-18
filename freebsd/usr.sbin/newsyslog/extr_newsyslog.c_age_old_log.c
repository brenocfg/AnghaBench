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
typedef  int time_t ;
struct stat {int st_mtime; } ;
struct TYPE_2__ {int /*<<< orphan*/  suffix; } ;

/* Variables and functions */
 int COMPRESS_TYPES ; 
 unsigned int MAX (unsigned int,int /*<<< orphan*/ ) ; 
 int MAXPATHLEN ; 
 char* alloca (size_t) ; 
 char* archdirname ; 
 scalar_t__ archtodir ; 
 TYPE_1__* compress_type ; 
 char* get_logfile_suffix (char*) ; 
 int mtime_old_timelog (char*) ; 
 int ptimeget_secs (int /*<<< orphan*/ ) ; 
 scalar_t__ stat (char*,struct stat*) ; 
 int /*<<< orphan*/  strlcat (char*,char const*,size_t) ; 
 int /*<<< orphan*/  strlcpy (char*,char const*,size_t) ; 
 int /*<<< orphan*/  strlen (int /*<<< orphan*/ ) ; 
 char* strrchr (char const*,char) ; 
 int /*<<< orphan*/ * timefnamefmt ; 
 int /*<<< orphan*/  timenow ; 

__attribute__((used)) static int
age_old_log(const char *file)
{
	struct stat sb;
	const char *logfile_suffix;
	static unsigned int suffix_maxlen = 0;
	char *tmp;
	size_t tmpsiz;
	time_t mtime;
	int c;

	if (suffix_maxlen == 0) {
		for (c = 0; c < COMPRESS_TYPES; c++)
			suffix_maxlen = MAX(suffix_maxlen,
			    strlen(compress_type[c].suffix));
	}

	tmpsiz = MAXPATHLEN + sizeof(".0") + suffix_maxlen + 1;
	tmp = alloca(tmpsiz);

	if (archtodir) {
		char *p;

		/* build name of archive directory into tmp */
		if (*archdirname == '/') {	/* absolute */
			strlcpy(tmp, archdirname, tmpsiz);
		} else {	/* relative */
			/* get directory part of logfile */
			strlcpy(tmp, file, tmpsiz);
			if ((p = strrchr(tmp, '/')) == NULL)
				tmp[0] = '\0';
			else
				*(p + 1) = '\0';
			strlcat(tmp, archdirname, tmpsiz);
		}

		strlcat(tmp, "/", tmpsiz);

		/* get filename part of logfile */
		if ((p = strrchr(file, '/')) == NULL)
			strlcat(tmp, file, tmpsiz);
		else
			strlcat(tmp, p + 1, tmpsiz);
	} else {
		(void) strlcpy(tmp, file, tmpsiz);
	}

	if (timefnamefmt != NULL) {
		mtime = mtime_old_timelog(tmp);
		if (mtime == -1)
			return (-1);
	} else {
		strlcat(tmp, ".0", tmpsiz);
		logfile_suffix = get_logfile_suffix(tmp);
		if (logfile_suffix == NULL)
			return (-1);
		(void) strlcat(tmp, logfile_suffix, tmpsiz);
		if (stat(tmp, &sb) < 0)
			return (-1);
		mtime = sb.st_mtime;
	}

	return ((int)(ptimeget_secs(timenow) - mtime + 1800) / 3600);
}