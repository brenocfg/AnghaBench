#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  isc_result_t ;
struct TYPE_4__ {char* dirname; int /*<<< orphan*/ * handle; } ;
typedef  TYPE_1__ isc_dir_t ;

/* Variables and functions */
 int /*<<< orphan*/  ISC_R_NOSPACE ; 
 int /*<<< orphan*/  ISC_R_SUCCESS ; 
 int /*<<< orphan*/  REQUIRE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VALID_DIR (TYPE_1__*) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  isc__errno2result (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * opendir (char const*) ; 
 int /*<<< orphan*/  strlcpy (char*,char const*,size_t) ; 
 size_t strlen (char const*) ; 

isc_result_t
isc_dir_open(isc_dir_t *dir, const char *dirname) {
	char *p;
	size_t octets;
	isc_result_t result = ISC_R_SUCCESS;

	REQUIRE(VALID_DIR(dir));
	REQUIRE(dirname != NULL);

	/*
	 * Copy directory name.  Need to have enough space for the name,
	 * a possible path separator, the wildcard, and the final NUL.
	 */
	octets = strlen(dirname) + 1;
	if (octets + 2 > sizeof(dir->dirname))
		/* XXXDCL ? */
		return (ISC_R_NOSPACE);
	strlcpy(dir->dirname, dirname, octets);

	/*
	 * Append path separator, if needed, and "*".
	 */
	p = dir->dirname + strlen(dir->dirname);
	if (dir->dirname < p && *(p - 1) != '/')
		*p++ = '/';
	*p++ = '*';
	*p = '\0';

	/*
	 * Open stream.
	 */
	dir->handle = opendir(dirname);

	if (dir->handle == NULL)
		return isc__errno2result(errno);

	return (result);
}