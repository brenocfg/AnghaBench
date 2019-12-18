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
struct stat {int dummy; } ;
typedef  int /*<<< orphan*/  isc_result_t ;

/* Variables and functions */
 int /*<<< orphan*/  ISC_R_SUCCESS ; 
 int /*<<< orphan*/  REQUIRE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  isc__errno2result (int /*<<< orphan*/ ) ; 
 scalar_t__ stat (char const*,struct stat*) ; 

__attribute__((used)) static isc_result_t
file_stats(const char *file, struct stat *stats) {
	isc_result_t result = ISC_R_SUCCESS;

	REQUIRE(file != NULL);
	REQUIRE(stats != NULL);

	if (stat(file, stats) != 0)
		result = isc__errno2result(errno);

	return (result);
}