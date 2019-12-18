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
 scalar_t__ ISC_R_NOSPACE ; 
 scalar_t__ ISC_R_SUCCESS ; 
 scalar_t__ dir_current (char*,size_t) ; 
 int /*<<< orphan*/  strlcat (char*,char const*,size_t) ; 
 int strlen (char const*) ; 

isc_result_t
isc_file_absolutepath(const char *filename, char *path, size_t pathlen) {
	isc_result_t result;
	result = dir_current(path, pathlen);
	if (result != ISC_R_SUCCESS)
		return (result);
	if (strlen(path) + strlen(filename) + 1 > pathlen)
		return (ISC_R_NOSPACE);
	strlcat(path, filename, pathlen);
	return (ISC_R_SUCCESS);
}