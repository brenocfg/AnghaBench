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
typedef  int vm_offset_t ;

/* Variables and functions */
 int PDRSHIFT ; 

__attribute__((used)) static __inline vm_pindex_t
pmap_pde_pindex(vm_offset_t va)
{
	return (va >> PDRSHIFT);
}