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
struct stat {int /*<<< orphan*/  st_mtime; } ;
typedef  int /*<<< orphan*/  isc_time_t ;
typedef  scalar_t__ isc_result_t ;

/* Variables and functions */
 scalar_t__ ISC_R_SUCCESS ; 
 int /*<<< orphan*/  REQUIRE (int /*<<< orphan*/ ) ; 
 scalar_t__ file_stats (char const*,struct stat*) ; 
 int /*<<< orphan*/  isc_time_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

isc_result_t
isc_file_getmodtime(const char *file, isc_time_t *itime) {
	isc_result_t result;
	struct stat stats;

	REQUIRE(file != NULL);
	REQUIRE(itime != NULL);

	result = file_stats(file, &stats);

	if (result == ISC_R_SUCCESS)
		/*
		 * XXXDCL some operating systems provide nanoseconds, too,
		 * such as BSD/OS via st_mtimespec.
		 */
		isc_time_set(itime, stats.st_mtime, 0);

	return (result);
}