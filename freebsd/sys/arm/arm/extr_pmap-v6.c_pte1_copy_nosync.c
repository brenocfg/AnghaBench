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
typedef  int /*<<< orphan*/  vm_offset_t ;
typedef  int u_int ;
typedef  int /*<<< orphan*/  pt1_entry_t ;

/* Variables and functions */
 int /*<<< orphan*/  bcopy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int pte1_index (int /*<<< orphan*/ ) ; 

__attribute__((used)) static __inline void
pte1_copy_nosync(pt1_entry_t *spte1p, pt1_entry_t *dpte1p, vm_offset_t sva,
    vm_offset_t eva)
{
	u_int idx, count;

	idx = pte1_index(sva);
	count = (pte1_index(eva) - idx + 1) * sizeof(pt1_entry_t);
	bcopy(spte1p + idx, dpte1p + idx, count);
}