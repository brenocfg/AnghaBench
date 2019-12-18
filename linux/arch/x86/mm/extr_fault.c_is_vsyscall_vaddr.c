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
 unsigned long PAGE_MASK ; 
 unsigned long VSYSCALL_ADDR ; 
 int unlikely (int) ; 

__attribute__((used)) static bool is_vsyscall_vaddr(unsigned long vaddr)
{
	return unlikely((vaddr & PAGE_MASK) == VSYSCALL_ADDR);
}