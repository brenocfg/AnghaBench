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
struct stat {int st_mode; } ;
typedef  scalar_t__ isc_result_t ;
typedef  int /*<<< orphan*/  isc_fsaccess_t ;
typedef  int /*<<< orphan*/  isc_boolean_t ;

/* Variables and functions */
 scalar_t__ FAT_fsaccess_set (char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ISC_FALSE ; 
 scalar_t__ ISC_R_INVALIDFILE ; 
 scalar_t__ ISC_R_SUCCESS ; 
 int /*<<< orphan*/  ISC_TRUE ; 
 scalar_t__ NTFS_fsaccess_set (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int S_IFDIR ; 
 int S_IFREG ; 
 scalar_t__ check_bad_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errno ; 
 scalar_t__ is_ntfs (char const*) ; 
 scalar_t__ isc__errno2result (int /*<<< orphan*/ ) ; 
 scalar_t__ stat (char const*,struct stat*) ; 

isc_result_t
isc_fsaccess_set(const char *path, isc_fsaccess_t access) {
	struct stat statb;
	isc_boolean_t is_dir = ISC_FALSE;
	isc_result_t result;

	if (stat(path, &statb) != 0)
		return (isc__errno2result(errno));

	if ((statb.st_mode & S_IFDIR) != 0)
		is_dir = ISC_TRUE;
	else if ((statb.st_mode & S_IFREG) == 0)
		return (ISC_R_INVALIDFILE);

	result = check_bad_bits(access, is_dir);
	if (result != ISC_R_SUCCESS)
		return (result);

	/*
	 * Determine if this is a FAT or NTFS disk and
	 * call the appropriate function to set the permissions
	 */
	if (is_ntfs(path))
		return (NTFS_fsaccess_set(path, access, is_dir));
	else
		return (FAT_fsaccess_set(path, access));
}