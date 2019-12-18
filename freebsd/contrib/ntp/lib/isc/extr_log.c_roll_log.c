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
typedef  int /*<<< orphan*/  new ;
typedef  scalar_t__ isc_result_t ;
typedef  int /*<<< orphan*/  isc_logchannel_t ;
typedef  int /*<<< orphan*/  current ;

/* Variables and functions */
 char* FILE_NAME (int /*<<< orphan*/ *) ; 
 int FILE_VERSIONS (int /*<<< orphan*/ *) ; 
 int ISC_LOG_ROLLINFINITE ; 
 int ISC_LOG_ROLLNEVER ; 
 scalar_t__ ISC_R_FILENOTFOUND ; 
 scalar_t__ ISC_R_NOSPACE ; 
 scalar_t__ ISC_R_SUCCESS ; 
 int /*<<< orphan*/  LOG_ERR ; 
 int /*<<< orphan*/  PATH_MAX ; 
 scalar_t__ greatest_version (int /*<<< orphan*/ *,int*) ; 
 scalar_t__ isc_file_remove (char const*) ; 
 scalar_t__ isc_file_rename (char const*,char*) ; 
 int /*<<< orphan*/  isc_result_totext (scalar_t__) ; 
 int snprintf (char*,int,char*,char const*,...) ; 
 int /*<<< orphan*/  syslog (int /*<<< orphan*/ ,char*,char const*,...) ; 

__attribute__((used)) static isc_result_t
roll_log(isc_logchannel_t *channel) {
	int i, n, greatest;
	char current[PATH_MAX + 1];
	char new[PATH_MAX + 1];
	const char *path;
	isc_result_t result;

	/*
	 * Do nothing (not even excess version trimming) if ISC_LOG_ROLLNEVER
	 * is specified.  Apparently complete external control over the log
	 * files is desired.
	 */
	if (FILE_VERSIONS(channel) == ISC_LOG_ROLLNEVER)
		return (ISC_R_SUCCESS);

	path = FILE_NAME(channel);

	/*
	 * Set greatest_version to the greatest existing version
	 * (not the maximum requested version).  This is 1 based even
	 * though the file names are 0 based, so an oldest log of log.1
	 * is a greatest_version of 2.
	 */
	result = greatest_version(channel, &greatest);
	if (result != ISC_R_SUCCESS)
		return (result);

	/*
	 * Now greatest should be set to the highest version number desired.
	 * Since the highest number is one less than FILE_VERSIONS(channel)
	 * when not doing infinite log rolling, greatest will need to be
	 * decremented when it is equal to -- or greater than --
	 * FILE_VERSIONS(channel).  When greatest is less than
	 * FILE_VERSIONS(channel), it is already suitable for use as
	 * the maximum version number.
	 */

	if (FILE_VERSIONS(channel) == ISC_LOG_ROLLINFINITE ||
	    FILE_VERSIONS(channel) > greatest)
		;		/* Do nothing. */
	else
		/*
		 * When greatest is >= FILE_VERSIONS(channel), it needs to
		 * be reduced until it is FILE_VERSIONS(channel) - 1.
		 * Remove any excess logs on the way to that value.
		 */
		while (--greatest >= FILE_VERSIONS(channel)) {
			n = snprintf(current, sizeof(current), "%s.%d",
				     path, greatest);
			if (n >= (int)sizeof(current) || n < 0)
				result = ISC_R_NOSPACE;
			else
				result = isc_file_remove(current);
			if (result != ISC_R_SUCCESS &&
			    result != ISC_R_FILENOTFOUND)
				syslog(LOG_ERR,
				       "unable to remove log file '%s.%d': %s",
				       path, greatest,
				       isc_result_totext(result));
		}

	for (i = greatest; i > 0; i--) {
		result = ISC_R_SUCCESS;
		n = snprintf(current, sizeof(current), "%s.%d", path, i - 1);
		if (n >= (int)sizeof(current) || n < 0)
			result = ISC_R_NOSPACE;
		if (result == ISC_R_SUCCESS) {
			n = snprintf(new, sizeof(new), "%s.%d", path, i);
			if (n >= (int)sizeof(new) || n < 0)
				result = ISC_R_NOSPACE;
		}
		if (result == ISC_R_SUCCESS)
			result = isc_file_rename(current, new);
		if (result != ISC_R_SUCCESS &&
		    result != ISC_R_FILENOTFOUND)
			syslog(LOG_ERR,
			       "unable to rename log file '%s.%d' to "
			       "'%s.%d': %s", path, i - 1, path, i,
			       isc_result_totext(result));
	}

	if (FILE_VERSIONS(channel) != 0) {
		n = snprintf(new, sizeof(new), "%s.0", path);
		if (n >= (int)sizeof(new) || n < 0)
			result = ISC_R_NOSPACE;
		else
			result = isc_file_rename(path, new);
		if (result != ISC_R_SUCCESS &&
		    result != ISC_R_FILENOTFOUND)
			syslog(LOG_ERR,
			       "unable to rename log file '%s' to '%s.0': %s",
			       path, path, isc_result_totext(result));
	} else {
		result = isc_file_remove(path);
		if (result != ISC_R_SUCCESS &&
		    result != ISC_R_FILENOTFOUND)
			syslog(LOG_ERR, "unable to remove log file '%s': %s",
			       path, isc_result_totext(result));
	}

	return (ISC_R_SUCCESS);
}