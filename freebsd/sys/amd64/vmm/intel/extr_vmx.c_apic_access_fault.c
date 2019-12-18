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
typedef  scalar_t__ uint64_t ;
struct vmx {int dummy; } ;

/* Variables and functions */
 scalar_t__ DEFAULT_APIC_BASE ; 
 scalar_t__ PAGE_SIZE ; 
 scalar_t__ apic_access_virtualization (struct vmx*,int) ; 

__attribute__((used)) static bool
apic_access_fault(struct vmx *vmx, int vcpuid, uint64_t gpa)
{

	if (apic_access_virtualization(vmx, vcpuid) &&
	    (gpa >= DEFAULT_APIC_BASE && gpa < DEFAULT_APIC_BASE + PAGE_SIZE))
		return (true);
	else
		return (false);
}