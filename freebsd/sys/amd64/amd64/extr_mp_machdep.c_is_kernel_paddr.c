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
typedef  scalar_t__ vm_paddr_t ;

/* Variables and functions */
 scalar_t__ KERNBASE ; 
 scalar_t__ _end ; 
 scalar_t__ btext ; 
 scalar_t__ round_page (scalar_t__) ; 
 scalar_t__ trunc_2mpage (scalar_t__) ; 

__attribute__((used)) static bool
is_kernel_paddr(vm_paddr_t pa)
{

	return (pa >= trunc_2mpage(btext - KERNBASE) &&
	   pa < round_page(_end - KERNBASE));
}