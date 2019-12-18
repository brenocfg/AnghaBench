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
typedef  int vm_offset_t ;

/* Variables and functions */
 int NPT2_IN_PG ; 
 int PTE1_SIZE ; 
 scalar_t__ pt2map_entry (int) ; 

__attribute__((used)) static __inline vm_offset_t
pt2map_pt2pg(vm_offset_t va)
{

	va &= ~(NPT2_IN_PG * PTE1_SIZE - 1);
	return ((vm_offset_t)pt2map_entry(va));
}