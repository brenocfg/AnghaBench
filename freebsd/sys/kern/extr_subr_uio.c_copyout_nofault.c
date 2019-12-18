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
 int copyout (void const*,void*,size_t) ; 
 int vm_fault_disable_pagefaults () ; 
 int /*<<< orphan*/  vm_fault_enable_pagefaults (int) ; 

int
copyout_nofault(const void *kaddr, void *udaddr, size_t len)
{
	int error, save;

	save = vm_fault_disable_pagefaults();
	error = copyout(kaddr, udaddr, len);
	vm_fault_enable_pagefaults(save);
	return (error);
}