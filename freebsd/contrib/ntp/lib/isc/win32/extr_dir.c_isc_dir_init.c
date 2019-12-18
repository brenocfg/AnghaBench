#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {char* name; int /*<<< orphan*/  find_data; scalar_t__ length; } ;
struct TYPE_5__ {char* dirname; int /*<<< orphan*/  magic; int /*<<< orphan*/  search_handle; int /*<<< orphan*/  entry_filled; TYPE_1__ entry; } ;
typedef  TYPE_2__ isc_dir_t ;

/* Variables and functions */
 int /*<<< orphan*/  INVALID_HANDLE_VALUE ; 
 int /*<<< orphan*/  ISC_DIR_MAGIC ; 
 int /*<<< orphan*/  ISC_FALSE ; 
 int /*<<< orphan*/  REQUIRE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

void
isc_dir_init(isc_dir_t *dir) {
	REQUIRE(dir != NULL);

	dir->dirname[0] = '\0';

	dir->entry.name[0] = '\0';
	dir->entry.length = 0;
	memset(&(dir->entry.find_data), 0, sizeof(dir->entry.find_data));

	dir->entry_filled = ISC_FALSE;
	dir->search_handle = INVALID_HANDLE_VALUE;

	dir->magic = ISC_DIR_MAGIC;
}