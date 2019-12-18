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
struct uv_irq_2_mmr_pnode {int /*<<< orphan*/  offset; int /*<<< orphan*/  pnode; } ;
struct uv_IO_APIC_route_entry {int /*<<< orphan*/  dest; scalar_t__ mask; scalar_t__ trigger; scalar_t__ polarity; int /*<<< orphan*/  dest_mode; int /*<<< orphan*/  delivery_mode; int /*<<< orphan*/  vector; } ;
struct irq_cfg {int /*<<< orphan*/  dest_apicid; int /*<<< orphan*/  vector; } ;
struct TYPE_2__ {int /*<<< orphan*/  irq_dest_mode; int /*<<< orphan*/  irq_delivery_mode; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUILD_BUG_ON (int) ; 
 TYPE_1__* apic ; 
 int /*<<< orphan*/  uv_write_global_mmr64 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned long) ; 

__attribute__((used)) static void uv_program_mmr(struct irq_cfg *cfg, struct uv_irq_2_mmr_pnode *info)
{
	unsigned long mmr_value;
	struct uv_IO_APIC_route_entry *entry;

	BUILD_BUG_ON(sizeof(struct uv_IO_APIC_route_entry) !=
		     sizeof(unsigned long));

	mmr_value = 0;
	entry = (struct uv_IO_APIC_route_entry *)&mmr_value;
	entry->vector		= cfg->vector;
	entry->delivery_mode	= apic->irq_delivery_mode;
	entry->dest_mode	= apic->irq_dest_mode;
	entry->polarity		= 0;
	entry->trigger		= 0;
	entry->mask		= 0;
	entry->dest		= cfg->dest_apicid;

	uv_write_global_mmr64(info->pnode, info->offset, mmr_value);
}