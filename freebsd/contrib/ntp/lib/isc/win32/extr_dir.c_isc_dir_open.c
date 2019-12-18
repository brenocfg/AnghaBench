#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  isc_result_t ;
struct TYPE_5__ {scalar_t__ search_handle; char* dirname; } ;
typedef  TYPE_1__ isc_dir_t ;

/* Variables and functions */
 scalar_t__ INVALID_HANDLE_VALUE ; 
 int /*<<< orphan*/  ISC_R_NOSPACE ; 
 int /*<<< orphan*/  REQUIRE (int) ; 
 scalar_t__ VALID_DIR (TYPE_1__*) ; 
 int /*<<< orphan*/  start_directory (TYPE_1__*) ; 
 int /*<<< orphan*/  strcpy (char*,char const*) ; 
 int strlen (char const*) ; 

isc_result_t
isc_dir_open(isc_dir_t *dir, const char *dirname) {
	char *p;
	isc_result_t result;

	REQUIRE(dirname != NULL);
	REQUIRE(VALID_DIR(dir) && dir->search_handle == INVALID_HANDLE_VALUE);

	/*
	 * Copy directory name.  Need to have enough space for the name,
	 * a possible path separator, the wildcard, and the final NUL.
	 */
	if (strlen(dirname) + 3 > sizeof(dir->dirname))
		/* XXXDCL ? */
		return (ISC_R_NOSPACE);
	strcpy(dir->dirname, dirname);

	/*
	 * Append path separator, if needed, and "*".
	 */
	p = dir->dirname + strlen(dir->dirname);
	if (dir->dirname < p && *(p - 1) != '\\' && *(p - 1) != ':')
		*p++ = '\\';
	*p++ = '*';
	*p = '\0';

	/*
	 * Open stream.
	 */
	result = start_directory(dir);

	return (result);
}