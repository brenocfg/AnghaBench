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
struct vlapic {int msr_apicbase; struct LAPIC* apic_page; } ;
struct LAPIC {int svr; } ;

/* Variables and functions */
 int APICBASE_ENABLED ; 
 int APIC_SVR_ENABLE ; 

bool
vlapic_enabled(struct vlapic *vlapic)
{
	struct LAPIC *lapic = vlapic->apic_page;

	if ((vlapic->msr_apicbase & APICBASE_ENABLED) != 0 &&
	    (lapic->svr & APIC_SVR_ENABLE) != 0)
		return (true);
	else
		return (false);
}