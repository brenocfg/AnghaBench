#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_5__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  isc_result_t ;
struct TYPE_8__ {int /*<<< orphan*/  cFileName; } ;
struct TYPE_6__ {int /*<<< orphan*/  name; int /*<<< orphan*/  length; TYPE_5__ find_data; } ;
struct TYPE_7__ {scalar_t__ search_handle; TYPE_1__ entry; scalar_t__ entry_filled; } ;
typedef  TYPE_2__ isc_dir_t ;

/* Variables and functions */
 scalar_t__ ERROR_NO_MORE_FILES ; 
 scalar_t__ FALSE ; 
 scalar_t__ FindNextFile (scalar_t__,TYPE_5__*) ; 
 scalar_t__ GetLastError () ; 
 scalar_t__ INVALID_HANDLE_VALUE ; 
 scalar_t__ ISC_FALSE ; 
 int /*<<< orphan*/  ISC_R_NOMORE ; 
 int /*<<< orphan*/  ISC_R_SUCCESS ; 
 int /*<<< orphan*/  ISC_R_UNEXPECTED ; 
 int /*<<< orphan*/  REQUIRE (int) ; 
 scalar_t__ VALID_DIR (TYPE_2__*) ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strlen (int /*<<< orphan*/ ) ; 

isc_result_t
isc_dir_read(isc_dir_t *dir) {
	REQUIRE(VALID_DIR(dir) && dir->search_handle != INVALID_HANDLE_VALUE);

	if (dir->entry_filled)
		/*
		 * start_directory() already filled in the first entry.
		 */
		dir->entry_filled = ISC_FALSE;

	else {
		/*
		 * Fetch next file in directory.
		 */
		if (FindNextFile(dir->search_handle,
				 &dir->entry.find_data) == FALSE)
			/*
			 * Either the last file has been processed or
			 * an error has occurred.  The former is not
			 * really an error, but the latter is.
			 */
			if (GetLastError() == ERROR_NO_MORE_FILES)
				return (ISC_R_NOMORE);
			else
				return (ISC_R_UNEXPECTED);
	}

	/*
	 * Make sure that the space for the name is long enough.
	 */
	strcpy(dir->entry.name, dir->entry.find_data.cFileName);
	dir->entry.length = strlen(dir->entry.name);

	return (ISC_R_SUCCESS);
}