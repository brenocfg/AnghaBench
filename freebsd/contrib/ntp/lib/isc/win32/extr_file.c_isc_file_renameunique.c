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

/* Variables and functions */
 scalar_t__ ISC_R_SUCCESS ; 
 int /*<<< orphan*/  REQUIRE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  errno ; 
 scalar_t__ isc__errno2result (int /*<<< orphan*/ ) ; 
 int isc_file_safemovefile (char const*,char*) ; 
 int mkstemp (char*) ; 
 int /*<<< orphan*/  unlink (char*) ; 

isc_result_t
isc_file_renameunique(const char *file, char *templet) {
	int fd = -1;
	int res = 0;
	isc_result_t result = ISC_R_SUCCESS;

	REQUIRE(file != NULL);
	REQUIRE(templet != NULL);

	fd = mkstemp(templet);
	if (fd == -1)
		result = isc__errno2result(errno);
	else
		close(fd);

	if (result == ISC_R_SUCCESS) {
		res = isc_file_safemovefile(file, templet);
		if (res != 0) {
			result = isc__errno2result(errno);
			(void)unlink(templet);
		}
	}
	return (result);
}