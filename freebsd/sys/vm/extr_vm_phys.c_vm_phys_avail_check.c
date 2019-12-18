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
typedef  int /*<<< orphan*/  intmax_t ;

/* Variables and functions */
 int PAGE_MASK ; 
 int /*<<< orphan*/  panic (char*,int,int /*<<< orphan*/ ,...) ; 
 int* phys_avail ; 

__attribute__((used)) static void
vm_phys_avail_check(int i)
{
	if (phys_avail[i] & PAGE_MASK)
		panic("Unaligned phys_avail[%d]: %#jx", i,
		    (intmax_t)phys_avail[i]);
	if (phys_avail[i+1] & PAGE_MASK)
		panic("Unaligned phys_avail[%d + 1]: %#jx", i,
		    (intmax_t)phys_avail[i]);
	if (phys_avail[i + 1] < phys_avail[i])
		panic("phys_avail[%d] start %#jx < end %#jx", i,
		    (intmax_t)phys_avail[i], (intmax_t)phys_avail[i+1]);
}