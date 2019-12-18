#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct page {int dummy; } ;
typedef  scalar_t__ efi_status_t ;
typedef  int /*<<< orphan*/  efi_physical_addr_t ;
typedef  int /*<<< orphan*/  efi_capsule_header_t ;
struct TYPE_2__ {scalar_t__ (* update_capsule ) (int /*<<< orphan*/ **,int,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 scalar_t__ EFI_SUCCESS ; 
 int EINVAL ; 
 int /*<<< orphan*/  capsule_mutex ; 
 int capsule_pending ; 
 TYPE_1__ efi ; 
 int efi_reset_type ; 
 int efi_status_to_err (scalar_t__) ; 
 int /*<<< orphan*/  lockdep_assert_held (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  page_to_phys (struct page*) ; 
 int /*<<< orphan*/  pr_err (char*,int,int) ; 
 int /*<<< orphan*/  pr_warn (char*) ; 
 int /*<<< orphan*/  stop_capsules ; 
 scalar_t__ stub1 (int /*<<< orphan*/ **,int,int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
efi_capsule_update_locked(efi_capsule_header_t *capsule,
			  struct page **sg_pages, int reset)
{
	efi_physical_addr_t sglist_phys;
	efi_status_t status;

	lockdep_assert_held(&capsule_mutex);

	/*
	 * If someone has already registered a capsule that requires a
	 * different reset type, we're out of luck and must abort.
	 */
	if (efi_reset_type >= 0 && efi_reset_type != reset) {
		pr_err("Conflicting capsule reset type %d (%d).\n",
		       reset, efi_reset_type);
		return -EINVAL;
	}

	/*
	 * If the system is getting ready to restart it may have
	 * called efi_capsule_pending() to make decisions (such as
	 * whether to force an EFI reboot), and we're racing against
	 * that call. Abort in that case.
	 */
	if (unlikely(stop_capsules)) {
		pr_warn("Capsule update raced with reboot, aborting.\n");
		return -EINVAL;
	}

	sglist_phys = page_to_phys(sg_pages[0]);

	status = efi.update_capsule(&capsule, 1, sglist_phys);
	if (status == EFI_SUCCESS) {
		capsule_pending = true;
		efi_reset_type = reset;
	}

	return efi_status_to_err(status);
}