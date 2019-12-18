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
struct TYPE_6__ {int length; int /*<<< orphan*/  name; TYPE_5__ find_data; } ;
struct TYPE_7__ {scalar_t__ search_handle; int /*<<< orphan*/  entry_filled; TYPE_1__ entry; int /*<<< orphan*/  dirname; } ;
typedef  TYPE_2__ isc_dir_t ;

/* Variables and functions */
 scalar_t__ FindFirstFile (int /*<<< orphan*/ ,TYPE_5__*) ; 
 int /*<<< orphan*/  INSIST (int) ; 
 scalar_t__ INVALID_HANDLE_VALUE ; 
 int /*<<< orphan*/  ISC_FALSE ; 
 int /*<<< orphan*/  ISC_R_FAILURE ; 
 int /*<<< orphan*/  ISC_R_SUCCESS ; 
 int /*<<< orphan*/  ISC_TRUE ; 
 int /*<<< orphan*/  REQUIRE (int) ; 
 int VALID_DIR (TYPE_2__*) ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int strlen (int /*<<< orphan*/ ) ; 

__attribute__((used)) static isc_result_t
start_directory(isc_dir_t *dir)
{
	REQUIRE(VALID_DIR(dir));
	REQUIRE(dir->search_handle == INVALID_HANDLE_VALUE);

	dir->entry_filled = ISC_FALSE;

	/*
	 * Open stream and retrieve first file.
	 */
	dir->search_handle = FindFirstFile(dir->dirname,
					    &dir->entry.find_data);

	if (dir->search_handle == INVALID_HANDLE_VALUE) {
		/*
		 * Something went wrong but we don't know what. GetLastError()
		 * could give us more information about the error, but the
		 * MSDN documentation is frustratingly thin about what
		 * possible errors could have resulted.  (Score one for
		 * the Unix manual pages.)  So there is just this lame error
		 * instead of being able to differentiate ISC_R_NOTFOUND
		 * from ISC_R_UNEXPECTED.
		 */
		return (ISC_R_FAILURE);
	}

	/*
	 * Make sure that the space for the name is long enough.
	 */
	INSIST(sizeof(dir->entry.name) >
	       strlen(dir->entry.find_data.cFileName));

	/*
	 * Fill in the data for the first entry of the directory.
	 */
	strcpy(dir->entry.name, dir->entry.find_data.cFileName);
	dir->entry.length = strlen(dir->entry.name);

	dir->entry_filled = ISC_TRUE;

	return (ISC_R_SUCCESS);
}