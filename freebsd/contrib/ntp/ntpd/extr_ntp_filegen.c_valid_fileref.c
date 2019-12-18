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

/* Variables and functions */
 char const DIR_SEP ; 
 int FALSE ; 
 int /*<<< orphan*/  LOG_ERR ; 
 int TRUE ; 
 int /*<<< orphan*/  msyslog (int /*<<< orphan*/ ,char*,char const*) ; 
 char* strchr (char const*,char const) ; 

__attribute__((used)) static int
valid_fileref(
	const char *	dir,
	const char *	fname
	)
{
	/*
	 * dir cannot be changed dynamically
	 * (within the context of filegen)
	 * so just reject basenames containing '..'
	 *
	 * ASSUMPTION:
	 *		file system parts 'below' dir may be
	 *		specified without infringement of security
	 *
	 *		restricting dir to legal values
	 *		has to be ensured by other means
	 * (however, it would be possible to perform some checks here...)
	 */
	const char *p;

	/*
	 * Just to catch, dumb errors opening up the world...
	 */
	if (NULL == dir || '\0' == dir[0])
		return FALSE;

	if (NULL == fname)
		return FALSE;

#ifdef SYS_WINNT
	/*
	 * Windows treats / equivalent to \, reject any / to ensure
	 * check below for DIR_SEP (\ on windows) are adequate.
	 */
	if (strchr(fname, '/')) {
		msyslog(LOG_ERR,
			"filegen filenames must not contain '/': %s",
			fname);
		return FALSE;
	}
#endif

	for (p = fname; p != NULL; p = strchr(p, DIR_SEP)) {
		if ('.' == p[0] && '.' == p[1] 
		    && ('\0' == p[2] || DIR_SEP == p[2]))
			return FALSE;
	}

	return TRUE;
}