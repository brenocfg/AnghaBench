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
typedef  int /*<<< orphan*/  isc_result_t ;

/* Variables and functions */
 int /*<<< orphan*/  ISC_R_NOSPACE ; 
 int /*<<< orphan*/  ISC_R_SUCCESS ; 
 int /*<<< orphan*/  REQUIRE (int /*<<< orphan*/ ) ; 
 char* isc_file_basename (char const*) ; 
 char* strchr (char const*,char) ; 
 int /*<<< orphan*/  strcpy (char*,char const*) ; 
 size_t strlen (char const*) ; 
 int /*<<< orphan*/  strncpy (char*,char const*,size_t) ; 

isc_result_t
isc_file_progname(const char *filename, char *progname, size_t namelen) {
	const char *s;
	char *p;
	size_t len;

	REQUIRE(filename != NULL);
	REQUIRE(progname != NULL);

	/*
	 * Strip the path from the name
	 */
	s = isc_file_basename(filename);
	if (s == NULL) {
		return (ISC_R_NOSPACE);
	}

	/*
	 * Strip any and all suffixes
	 */
	p = strchr(s, '.');
	if (p == NULL) {
		if (namelen <= strlen(s))
			return (ISC_R_NOSPACE);

		strcpy(progname, s);
		return (ISC_R_SUCCESS);
	}

	/*
	 * Copy the result to the buffer
	 */
	len = p - s;
	if (len >= namelen)
		return (ISC_R_NOSPACE);

	strncpy(progname, s, len);
	progname[len] = '\0';
	return (ISC_R_SUCCESS);
}