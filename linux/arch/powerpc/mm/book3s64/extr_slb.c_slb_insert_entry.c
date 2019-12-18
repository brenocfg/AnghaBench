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
typedef  enum slb_index { ____Placeholder_slb_index } slb_index ;

/* Variables and functions */
 long EFAULT ; 
 unsigned long __mk_vsid_data (unsigned long,int,unsigned long) ; 
 int alloc_slb_index (int) ; 
 int /*<<< orphan*/  assert_slb_presence (int,unsigned long) ; 
 int /*<<< orphan*/  barrier () ; 
 unsigned long get_vsid (unsigned long,unsigned long,int) ; 
 unsigned long mk_esid_data (unsigned long,int,int) ; 
 int /*<<< orphan*/  slb_cache_update (unsigned long) ; 

__attribute__((used)) static long slb_insert_entry(unsigned long ea, unsigned long context,
				unsigned long flags, int ssize, bool kernel)
{
	unsigned long vsid;
	unsigned long vsid_data, esid_data;
	enum slb_index index;

	vsid = get_vsid(context, ea, ssize);
	if (!vsid)
		return -EFAULT;

	/*
	 * There must not be a kernel SLB fault in alloc_slb_index or before
	 * slbmte here or the allocation bitmaps could get out of whack with
	 * the SLB.
	 *
	 * User SLB faults or preloads take this path which might get inlined
	 * into the caller, so add compiler barriers here to ensure unsafe
	 * memory accesses do not come between.
	 */
	barrier();

	index = alloc_slb_index(kernel);

	vsid_data = __mk_vsid_data(vsid, ssize, flags);
	esid_data = mk_esid_data(ea, ssize, index);

	/*
	 * No need for an isync before or after this slbmte. The exception
	 * we enter with and the rfid we exit with are context synchronizing.
	 * User preloads should add isync afterwards in case the kernel
	 * accesses user memory before it returns to userspace with rfid.
	 */
	assert_slb_presence(false, ea);
	asm volatile("slbmte %0, %1" : : "r" (vsid_data), "r" (esid_data));

	barrier();

	if (!kernel)
		slb_cache_update(esid_data);

	return 0;
}