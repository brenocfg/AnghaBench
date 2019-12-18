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
typedef  int /*<<< orphan*/  swap_w_prefix ;
struct storage_entry {scalar_t__ allocationFailures; int /*<<< orphan*/  used; int /*<<< orphan*/  size; int /*<<< orphan*/  allocationUnits; int /*<<< orphan*/ * type; int /*<<< orphan*/  flags; } ;
struct kvm_swap {int dummy; } ;
typedef  int /*<<< orphan*/  nswapdev ;
struct TYPE_5__ {int /*<<< orphan*/  ksw_used; int /*<<< orphan*/  ksw_total; int /*<<< orphan*/  ksw_devname; } ;

/* Variables and functions */
 int /*<<< orphan*/  HRDBG (char*,int) ; 
 int /*<<< orphan*/  HR_STORAGE_FOUND ; 
 int /*<<< orphan*/  LOG_ERR ; 
 int /*<<< orphan*/  OIDX_hrStorageVirtualMemory_c ; 
 int SE_DESC_MLEN ; 
 char* _PATH_DEV ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  getpagesize () ; 
 int /*<<< orphan*/  hr_kd ; 
 int kvm_getswapinfo (int /*<<< orphan*/ ,TYPE_1__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (char*,char,int) ; 
 TYPE_1__* reallocf (TYPE_1__*,int) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char*,int /*<<< orphan*/ ) ; 
 struct storage_entry* storage_entry_create (char*) ; 
 struct storage_entry* storage_find_by_name (char*) ; 
 TYPE_1__* swap_devs ; 
 int swap_devs_len ; 
 scalar_t__ sysctlbyname (char*,int*,size_t*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  syslog (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void
storage_OS_get_swap(void)
{
	struct storage_entry *entry;
	char swap_w_prefix[SE_DESC_MLEN];
	size_t len;
	int nswapdev;

	len = sizeof(nswapdev);
	nswapdev = 0;

	if (sysctlbyname("vm.nswapdev", &nswapdev, &len, NULL,0 ) < 0) {
		syslog(LOG_ERR,
		    "hrStorageTable: sysctlbyname(\"vm.nswapdev\") "
		    "failed. %m");
		assert(0);
		return;
	}

	if (nswapdev <= 0) {
		HRDBG("vm.nswapdev is %d", nswapdev);
		return;
	}

	if (nswapdev + 1 != (int)swap_devs_len || swap_devs == NULL) {
		swap_devs_len = nswapdev + 1;
		swap_devs = reallocf(swap_devs,
		    swap_devs_len * sizeof(struct kvm_swap));

		assert(swap_devs != NULL);
		if (swap_devs == NULL) {
			swap_devs_len = 0;
			return;
		}
	}

	nswapdev = kvm_getswapinfo(hr_kd, swap_devs, swap_devs_len, 0);
	if (nswapdev < 0) {
		syslog(LOG_ERR,
		    "hrStorageTable: kvm_getswapinfo failed. %m\n");
		assert(0);
		return;
	}

	for (len = 0; len < (size_t)nswapdev; len++) {
		memset(&swap_w_prefix[0], '\0', sizeof(swap_w_prefix));
		snprintf(swap_w_prefix, sizeof(swap_w_prefix) - 1,
		    "Swap:%s%s", _PATH_DEV, swap_devs[len].ksw_devname);

		entry = storage_find_by_name(swap_w_prefix);
		if (entry == NULL)
			entry = storage_entry_create(swap_w_prefix);

		assert (entry != NULL);
		if (entry == NULL)
			return; /* Out of luck */

		entry->flags |= HR_STORAGE_FOUND;
		entry->type = &OIDX_hrStorageVirtualMemory_c;
		entry->allocationUnits = getpagesize();
		entry->size = swap_devs[len].ksw_total;
		entry->used = swap_devs[len].ksw_used;
		entry->allocationFailures = 0;
	}
}