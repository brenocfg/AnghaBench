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
typedef  int uint32_t ;

/* Variables and functions */
 int APIC_ID_SHIFT ; 
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int /*<<< orphan*/  LAPIC_ID ; 
 int /*<<< orphan*/ * lapic_map ; 
 int lapic_read32 (int /*<<< orphan*/ ) ; 
 scalar_t__ x2apic_mode ; 

__attribute__((used)) static int
native_lapic_id(void)
{
	uint32_t v;

	KASSERT(x2apic_mode || lapic_map != NULL, ("local APIC is not mapped"));
	v = lapic_read32(LAPIC_ID);
	if (!x2apic_mode)
		v >>= APIC_ID_SHIFT;
	return (v);
}