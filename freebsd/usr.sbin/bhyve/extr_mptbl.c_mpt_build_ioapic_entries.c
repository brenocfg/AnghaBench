#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* io_apic_entry_ptr ;
struct TYPE_4__ {int apic_id; int /*<<< orphan*/  apic_address; int /*<<< orphan*/  apic_flags; int /*<<< orphan*/  apic_version; int /*<<< orphan*/  type; } ;

/* Variables and functions */
 int /*<<< orphan*/  IOAPICENTRY_FLAG_EN ; 
 int /*<<< orphan*/  IOAPIC_PADDR ; 
 int /*<<< orphan*/  IOAPIC_VERSION ; 
 int /*<<< orphan*/  MPCT_ENTRY_IOAPIC ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
mpt_build_ioapic_entries(io_apic_entry_ptr mpei, int id)
{

	memset(mpei, 0, sizeof(*mpei));
	mpei->type = MPCT_ENTRY_IOAPIC;
	mpei->apic_id = id;
	mpei->apic_version = IOAPIC_VERSION;
	mpei->apic_flags = IOAPICENTRY_FLAG_EN;
	mpei->apic_address = IOAPIC_PADDR;
}