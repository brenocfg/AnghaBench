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
struct sfi_device_table_entry {int /*<<< orphan*/  irq; } ;
typedef  enum intel_msic_block { ____Placeholder_intel_msic_block } intel_msic_block ;
struct TYPE_2__ {int /*<<< orphan*/ * irq; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int INTEL_MSIC_BLOCK_LAST ; 
 TYPE_1__ msic_pdata ; 

void *msic_generic_platform_data(void *info, enum intel_msic_block block)
{
	struct sfi_device_table_entry *entry = info;

	BUG_ON(block < 0 || block >= INTEL_MSIC_BLOCK_LAST);
	msic_pdata.irq[block] = entry->irq;

	return NULL;
}