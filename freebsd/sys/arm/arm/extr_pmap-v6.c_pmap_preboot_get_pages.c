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
typedef  int vm_paddr_t ;
typedef  int u_int ;

/* Variables and functions */
 int PAGE_SIZE ; 
 int last_paddr ; 

vm_paddr_t
pmap_preboot_get_pages(u_int num)
{
	vm_paddr_t ret;

	ret = last_paddr;
	last_paddr += num * PAGE_SIZE;

	return (ret);
}