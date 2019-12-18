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
typedef  int u_int ;

/* Variables and functions */
 uintptr_t ADDR_SR_SHFT ; 

__attribute__((used)) static __inline int
va_to_sr(u_int *sr, vm_offset_t va)
{
	return (sr[(uintptr_t)va >> ADDR_SR_SHFT]);
}