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
typedef  scalar_t__ u_int ;

/* Variables and functions */
 scalar_t__ pmap_mapdev (scalar_t__,scalar_t__) ; 
 scalar_t__ trunc_page (scalar_t__) ; 

__attribute__((used)) static vm_offset_t
s3lfb_map_buffer(u_int paddr, size_t size)
{
	vm_offset_t vaddr;
	u_int off;

	off = paddr - trunc_page(paddr);
	vaddr = (vm_offset_t)pmap_mapdev(paddr - off, size + off);

	return (vaddr + off);
}