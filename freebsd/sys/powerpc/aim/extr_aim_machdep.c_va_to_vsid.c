#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ vm_offset_t ;
typedef  int uint64_t ;
typedef  TYPE_1__* pmap_t ;
struct TYPE_3__ {int* pm_sr; } ;

/* Variables and functions */
 uintptr_t ADDR_SR_SHFT ; 
 int SR_VSID_MASK ; 

uint64_t
va_to_vsid(pmap_t pm, vm_offset_t va)
{
	return ((pm->pm_sr[(uintptr_t)va >> ADDR_SR_SHFT]) & SR_VSID_MASK);
}