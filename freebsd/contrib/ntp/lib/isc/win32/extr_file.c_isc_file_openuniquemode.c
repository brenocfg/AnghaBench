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
typedef  scalar_t__ isc_result_t ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 scalar_t__ ISC_R_SUCCESS ; 
 int /*<<< orphan*/  REQUIRE (int) ; 
 int /*<<< orphan*/  UNUSED (int) ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  fchmod (int,int) ; 
 int /*<<< orphan*/ * fdopen (int,char*) ; 
 scalar_t__ isc__errno2result (int /*<<< orphan*/ ) ; 
 int mkstemp (char*) ; 
 int /*<<< orphan*/  remove (char*) ; 

isc_result_t
isc_file_openuniquemode(char *templet, int mode, FILE **fp) {
	int fd;
	FILE *f;
	isc_result_t result = ISC_R_SUCCESS;

	REQUIRE(templet != NULL);
	REQUIRE(fp != NULL && *fp == NULL);

	/*
	 * Win32 does not have mkstemp. Using emulation above.
	 */
	fd = mkstemp(templet);

	if (fd == -1)
		result = isc__errno2result(errno);
	if (result == ISC_R_SUCCESS) {
#if 1
		UNUSED(mode);
#else
		(void)fchmod(fd, mode);
#endif
		f = fdopen(fd, "w+");
		if (f == NULL) {
			result = isc__errno2result(errno);
			(void)remove(templet);
			(void)close(fd);
		} else
			*fp = f;
	}

	return (result);
}