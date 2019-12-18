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
struct stat {scalar_t__ st_mtime; scalar_t__ st_ctime; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int FALSE ; 
 int /*<<< orphan*/  LOG_ERR ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char const*,char*) ; 
 int leapsec_load_stream (int /*<<< orphan*/ *,char const*,int) ; 
 int /*<<< orphan*/  logPrefix ; 
 int /*<<< orphan*/  msyslog (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,char const*) ; 
 scalar_t__ stat (char const*,struct stat*) ; 

int/*BOOL*/
leapsec_load_file(
	const char  * fname,
	struct stat * sb_old,
	int/*BOOL*/   force,
	int/*BOOL*/   logall)
{
	FILE       * fp;
	struct stat  sb_new;
	int          rc;

	/* just do nothing if there is no leap file */
	if ( !(fname && *fname) )
		return FALSE;

	/* try to stat the leapfile */
	if (0 != stat(fname, &sb_new)) {
		if (logall)
			msyslog(LOG_ERR, "%s ('%s'): stat failed: %m",
				logPrefix, fname);
		return FALSE;
	}

	/* silently skip to postcheck if no new file found */
	if (NULL != sb_old) {
		if (!force
		 && sb_old->st_mtime == sb_new.st_mtime
		 && sb_old->st_ctime == sb_new.st_ctime
		   )
			return FALSE;
		*sb_old = sb_new;
	}

	/* try to open the leap file, complain if that fails
	 *
	 * [perlinger@ntp.org]
	 * coverity raises a TOCTOU (time-of-check/time-of-use) issue
	 * here, which is not entirely helpful: While there is indeed a
	 * possible race condition between the 'stat()' call above and
	 * the 'fopen)' call below, I intentionally want to omit the
	 * overhead of opening the file and calling 'fstat()', because
	 * in most cases the file would have be to closed anyway without
	 * reading the contents.  I chose to disable the coverity
	 * warning instead.
	 *
	 * So unless someone comes up with a reasonable argument why
	 * this could be a real issue, I'll just try to silence coverity
	 * on that topic.
	 */
	/* coverity[toctou] */
	if ((fp = fopen(fname, "r")) == NULL) {
		if (logall)
			msyslog(LOG_ERR,
				"%s ('%s'): open failed: %m",
				logPrefix, fname);
		return FALSE;
	}

	rc = leapsec_load_stream(fp, fname, logall);
	fclose(fp);
	return rc;
}