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
typedef  scalar_t__ vm_offset_t ;
typedef  int u_long ;

/* Variables and functions */
 int watch_virt_set_mask (scalar_t__,int) ; 

int
watch_virt_set(vm_offset_t va, int sz)
{
	u_long off;

	off = (u_long)va & 7;
	/* Test for misaligned watch points. */
	if (off + sz > 8)
		return (-1);
	return (watch_virt_set_mask(va, ((1 << sz) - 1) << off));
}