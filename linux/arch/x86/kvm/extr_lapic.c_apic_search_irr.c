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
struct kvm_lapic {scalar_t__ regs; } ;

/* Variables and functions */
 scalar_t__ APIC_IRR ; 
 int find_highest_vector (scalar_t__) ; 

__attribute__((used)) static inline int apic_search_irr(struct kvm_lapic *apic)
{
	return find_highest_vector(apic->regs + APIC_IRR);
}