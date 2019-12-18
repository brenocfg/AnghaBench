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
 int /*<<< orphan*/  memcpy (char*,char const*,size_t) ; 
 int strlen (char const*) ; 

isc_result_t
isc_file_progname(const char *filename, char *buf, size_t buflen) {
	const char *base;
	size_t len;

	REQUIRE(filename != NULL);
	REQUIRE(buf != NULL);

	base = isc_file_basename(filename);
	len = strlen(base) + 1;

	if (len > buflen)
		return (ISC_R_NOSPACE);
	memcpy(buf, base, len);

	return (ISC_R_SUCCESS);
}