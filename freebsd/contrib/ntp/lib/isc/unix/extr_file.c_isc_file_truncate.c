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
typedef  int /*<<< orphan*/  isc_offset_t ;

/* Variables and functions */
 int /*<<< orphan*/  ISC_R_SUCCESS ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  isc__errno2result (int /*<<< orphan*/ ) ; 
 scalar_t__ truncate (char const*,int /*<<< orphan*/ ) ; 

isc_result_t
isc_file_truncate(const char *filename, isc_offset_t size) {
	isc_result_t result = ISC_R_SUCCESS;

	if (truncate(filename, size) < 0)
		result = isc__errno2result(errno);
	return (result);
}