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
struct malloc_type {int /*<<< orphan*/  ks_shortdesc; } ;

/* Variables and functions */
 scalar_t__ memguard_cmp (unsigned long) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vm_memguard_desc ; 
 struct malloc_type* vm_memguard_mtype ; 

int
memguard_cmp_mtp(struct malloc_type *mtp, unsigned long size)
{

	if (memguard_cmp(size))
		return(1);

#if 1
	/*
	 * The safest way of comparsion is to always compare short description
	 * string of memory type, but it is also the slowest way.
	 */
	return (strcmp(mtp->ks_shortdesc, vm_memguard_desc) == 0);
#else
	/*
	 * If we compare pointers, there are two possible problems:
	 * 1. Memory type was unloaded and new memory type was allocated at the
	 *    same address.
	 * 2. Memory type was unloaded and loaded again, but allocated at a
	 *    different address.
	 */
	if (vm_memguard_mtype != NULL)
		return (mtp == vm_memguard_mtype);
	if (strcmp(mtp->ks_shortdesc, vm_memguard_desc) == 0) {
		vm_memguard_mtype = mtp;
		return (1);
	}
	return (0);
#endif
}