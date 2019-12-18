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

/* Variables and functions */
 scalar_t__ VM_MAXCPU ; 
 int /*<<< orphan*/  new_unrhdr (scalar_t__,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vpid_unr ; 

__attribute__((used)) static void
vpid_init(void)
{
	/*
	 * VPID 0 is required when the "enable VPID" execution control is
	 * disabled.
	 *
	 * VPIDs [1,VM_MAXCPU] are used as the "overflow namespace" when the
	 * unit number allocator does not have sufficient unique VPIDs to
	 * satisfy the allocation.
	 *
	 * The remaining VPIDs are managed by the unit number allocator.
	 */
	vpid_unr = new_unrhdr(VM_MAXCPU + 1, 0xffff, NULL);
}