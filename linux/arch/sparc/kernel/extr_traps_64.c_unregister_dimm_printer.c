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
typedef  int /*<<< orphan*/ * dimm_printer_t ;

/* Variables and functions */
 int /*<<< orphan*/ * dimm_handler ; 
 int /*<<< orphan*/  dimm_handler_lock ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

void unregister_dimm_printer(dimm_printer_t func)
{
	unsigned long flags;

	spin_lock_irqsave(&dimm_handler_lock, flags);
	if (dimm_handler == func)
		dimm_handler = NULL;
	spin_unlock_irqrestore(&dimm_handler_lock, flags);
}