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

/* Variables and functions */
 int /*<<< orphan*/  __cmci_disable_bank (int) ; 
 int /*<<< orphan*/  cmci_discover_lock ; 
 int /*<<< orphan*/  cmci_supported (int*) ; 
 int /*<<< orphan*/  raw_spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  raw_spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

void cmci_disable_bank(int bank)
{
	int banks;
	unsigned long flags;

	if (!cmci_supported(&banks))
		return;

	raw_spin_lock_irqsave(&cmci_discover_lock, flags);
	__cmci_disable_bank(bank);
	raw_spin_unlock_irqrestore(&cmci_discover_lock, flags);
}