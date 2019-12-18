#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {scalar_t__ config_type; } ;

/* Variables and functions */
 int /*<<< orphan*/  APIC_ID_ALL ; 
 int /*<<< orphan*/  APIC_LVT_DM_EXTINT ; 
 int /*<<< orphan*/  APIC_LVT_DM_NMI ; 
 int /*<<< orphan*/  APIC_LVT_LINT0 ; 
 int /*<<< orphan*/  APIC_LVT_LINT1 ; 
 int /*<<< orphan*/  lapic_set_lvt_mode (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__* mpfps ; 
 int /*<<< orphan*/  mptable_parse_default_config_ints () ; 
 int /*<<< orphan*/  mptable_parse_ints_handler ; 
 int /*<<< orphan*/  mptable_walk_table (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
mptable_parse_ints(void)
{

	/* Is this a pre-defined config? */
	if (mpfps->config_type != 0) {
		/* Configure LINT pins. */
		lapic_set_lvt_mode(APIC_ID_ALL, APIC_LVT_LINT0,
		    APIC_LVT_DM_EXTINT);
		lapic_set_lvt_mode(APIC_ID_ALL, APIC_LVT_LINT1, APIC_LVT_DM_NMI);

		/* Configure I/O APIC pins. */
		mptable_parse_default_config_ints();
	} else
		mptable_walk_table(mptable_parse_ints_handler, NULL);
}