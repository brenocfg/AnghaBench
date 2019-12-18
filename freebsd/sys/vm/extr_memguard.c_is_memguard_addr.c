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

/* Variables and functions */
 scalar_t__ memguard_base ; 
 scalar_t__ memguard_mapsize ; 

int
is_memguard_addr(void *addr)
{
	vm_offset_t a = (vm_offset_t)(uintptr_t)addr;

	return (a >= memguard_base && a < memguard_base + memguard_mapsize);
}