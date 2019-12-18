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
struct printer {char* jobnum; int jobdfnum; int /*<<< orphan*/  tr_timestr; int /*<<< orphan*/  tr_start; } ;

/* Variables and functions */
 scalar_t__ TIMESTR_SIZE ; 
 int /*<<< orphan*/  lpd_gettime (int /*<<< orphan*/ *,int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  memset (char*,int /*<<< orphan*/ ,int) ; 
 char* strchr (char const*,char) ; 

void
trstat_init(struct printer *pp, const char *fname, int filenum)
{
	register const char *srcp;
	register char *destp, *endp;

	/*
	 * Figure out the job id of this file.  The filename should be
	 * 'cf', 'df', or maybe 'tf', followed by a letter (or sometimes
	 * two), followed by the jobnum, followed by a hostname.
	 * The jobnum is usually 3 digits, but might be as many as 5.
	 * Note that some care has to be taken parsing this, as the
	 * filename could be coming from a remote-host, and thus might
	 * not look anything like what is expected...
	 */
	memset(pp->jobnum, 0, sizeof(pp->jobnum));
	pp->jobnum[0] = '0';
	srcp = strchr(fname, '/');
	if (srcp == NULL)
		srcp = fname;
	destp = &(pp->jobnum[0]);
	endp = destp + 5;
	while (*srcp != '\0' && (*srcp < '0' || *srcp > '9'))
		srcp++;
	while (*srcp >= '0' && *srcp <= '9' && destp < endp)
		*(destp++) = *(srcp++);

	/* get the starting time in both numeric and string formats, and
	 * save those away along with the file-number */
	pp->jobdfnum = filenum;
	lpd_gettime(&pp->tr_start, pp->tr_timestr, (size_t)TIMESTR_SIZE);

	return;
}