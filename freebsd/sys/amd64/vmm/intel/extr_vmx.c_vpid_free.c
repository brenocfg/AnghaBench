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
 int VM_MAXCPU ; 
 int /*<<< orphan*/  free_unr (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  panic (char*,int) ; 
 int /*<<< orphan*/  vpid_unr ; 

__attribute__((used)) static void
vpid_free(int vpid)
{
	if (vpid < 0 || vpid > 0xffff)
		panic("vpid_free: invalid vpid %d", vpid);

	/*
	 * VPIDs [0,VM_MAXCPU] are special and are not allocated from
	 * the unit number allocator.
	 */

	if (vpid > VM_MAXCPU)
		free_unr(vpid_unr, vpid);
}