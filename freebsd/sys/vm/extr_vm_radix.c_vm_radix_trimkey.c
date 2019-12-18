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
typedef  int vm_pindex_t ;
typedef  int uint16_t ;

/* Variables and functions */
 int VM_RADIX_WIDTH ; 

__attribute__((used)) static __inline vm_pindex_t
vm_radix_trimkey(vm_pindex_t index, uint16_t level)
{
	vm_pindex_t ret;

	ret = index;
	if (level > 0) {
		ret >>= level * VM_RADIX_WIDTH;
		ret <<= level * VM_RADIX_WIDTH;
	}
	return (ret);
}