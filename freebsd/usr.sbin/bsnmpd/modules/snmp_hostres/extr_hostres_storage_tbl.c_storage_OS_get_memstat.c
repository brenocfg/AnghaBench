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
typedef  scalar_t__ uint64_t ;
struct storage_entry {scalar_t__ allocationFailures; scalar_t__ used; scalar_t__ size; scalar_t__ allocationUnits; int /*<<< orphan*/ * type; int /*<<< orphan*/  flags; } ;
struct memory_type {int dummy; } ;
typedef  scalar_t__ int32_t ;
typedef  int /*<<< orphan*/  alloc_descr ;

/* Variables and functions */
#define  ALLOCATOR_MALLOC 129 
#define  ALLOCATOR_UMA 128 
 int /*<<< orphan*/  HRDBG (char*) ; 
 int /*<<< orphan*/  HR_STORAGE_FOUND ; 
 scalar_t__ INT_MAX ; 
 int /*<<< orphan*/  LOG_ERR ; 
 int /*<<< orphan*/  OIDX_hrStorageRam_c ; 
 int SE_DESC_MLEN ; 
 int memstat_get_allocator (struct memory_type*) ; 
 scalar_t__ memstat_get_count (struct memory_type*) ; 
 scalar_t__ memstat_get_countlimit (struct memory_type*) ; 
 scalar_t__ memstat_get_failures (struct memory_type*) ; 
 char* memstat_get_name (struct memory_type*) ; 
 scalar_t__ memstat_get_size (struct memory_type*) ; 
 scalar_t__ memstat_get_sizemask (struct memory_type*) ; 
 int /*<<< orphan*/ * memstat_mtl_alloc () ; 
 struct memory_type* memstat_mtl_first (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memstat_mtl_geterror (int /*<<< orphan*/ *) ; 
 struct memory_type* memstat_mtl_next (struct memory_type*) ; 
 int /*<<< orphan*/  memstat_strerror (int /*<<< orphan*/ ) ; 
 scalar_t__ memstat_sysctl_all (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * mt_list ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,...) ; 
 struct storage_entry* storage_entry_create (char*) ; 
 struct storage_entry* storage_find_by_name (char*) ; 
 scalar_t__ strlen (char const*) ; 
 int /*<<< orphan*/  syslog (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
storage_OS_get_memstat(void)
{
	struct memory_type *mt_item;
	struct storage_entry *entry;

	if (mt_list == NULL) {
		if ((mt_list = memstat_mtl_alloc()) == NULL)
			/* again? we have a serious problem */
		return;
	}

	if (memstat_sysctl_all(mt_list, 0) < 0) {
		syslog(LOG_ERR, "memstat_sysctl_all failed: %s",
		    memstat_strerror(memstat_mtl_geterror(mt_list)) );
		return;
	}

	if ((mt_item = memstat_mtl_first(mt_list)) == NULL) {
		/* usually this is not an error, no errno for this failure*/
		HRDBG("memstat_mtl_first failed");
		return;
	}

	do {
		const char *memstat_name;
		uint64_t tmp_size;
		int allocator;
		char alloc_descr[SE_DESC_MLEN];

		memstat_name = memstat_get_name(mt_item);

		if (memstat_name == NULL || strlen(memstat_name) == 0)
			continue;

		switch (allocator = memstat_get_allocator(mt_item)) {

		  case ALLOCATOR_MALLOC:
			snprintf(alloc_descr, sizeof(alloc_descr),
			    "MALLOC: %s", memstat_name);
			break;

		  case ALLOCATOR_UMA:
			snprintf(alloc_descr, sizeof(alloc_descr),
			    "UMA: %s", memstat_name);
			break;

		  default:
			snprintf(alloc_descr, sizeof(alloc_descr),
			    "UNKNOWN%d: %s", allocator, memstat_name);
			break;
		}

		if ((entry = storage_find_by_name(alloc_descr)) == NULL &&
		    (entry = storage_entry_create(alloc_descr)) == NULL)
			return;

		entry->flags |= HR_STORAGE_FOUND;
		entry->type = &OIDX_hrStorageRam_c;

		if ((tmp_size = memstat_get_size(mt_item)) == 0)
			tmp_size = memstat_get_sizemask(mt_item);
		entry->allocationUnits =
		    (tmp_size  > INT_MAX ? INT_MAX : (int32_t)tmp_size);

		tmp_size  = memstat_get_countlimit(mt_item);
		entry->size =
		    (tmp_size  > INT_MAX ? INT_MAX : (int32_t)tmp_size);

		tmp_size = memstat_get_count(mt_item);
		entry->used =
		    (tmp_size  > INT_MAX ? INT_MAX : (int32_t)tmp_size);

		tmp_size = memstat_get_failures(mt_item);
		entry->allocationFailures =
		    (tmp_size  > INT_MAX ? INT_MAX : (int32_t)tmp_size);

	} while((mt_item = memstat_mtl_next(mt_item)) != NULL);
}