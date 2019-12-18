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
typedef  int u64 ;
typedef  enum lapic_mode { ____Placeholder_lapic_mode } lapic_mode ;

/* Variables and functions */
 int MSR_IA32_APICBASE_ENABLE ; 
 int X2APIC_ENABLE ; 

__attribute__((used)) static inline enum lapic_mode kvm_apic_mode(u64 apic_base)
{
	return apic_base & (MSR_IA32_APICBASE_ENABLE | X2APIC_ENABLE);
}