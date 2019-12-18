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
typedef  scalar_t__ u64 ;
struct acpi_processor_tx_tss {scalar_t__ control; } ;
struct TYPE_2__ {int state_count; int /*<<< orphan*/ * states_tss; } ;
struct acpi_processor {TYPE_1__ throttling; } ;

/* Variables and functions */

__attribute__((used)) static int acpi_get_throttling_state(struct acpi_processor *pr,
				u64 value)
{
	int i;

	for (i = 0; i < pr->throttling.state_count; i++) {
		struct acpi_processor_tx_tss *tx =
		    (struct acpi_processor_tx_tss *)&(pr->throttling.
						      states_tss[i]);
		if (tx->control == value)
			return i;
	}
	return -1;
}