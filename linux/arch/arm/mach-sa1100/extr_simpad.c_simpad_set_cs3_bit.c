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
 int /*<<< orphan*/  __simpad_write_cs3 () ; 
 int /*<<< orphan*/  cs3_lock ; 
 int cs3_shadow ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

void simpad_set_cs3_bit(int value)
{
	unsigned long flags;

	spin_lock_irqsave(&cs3_lock, flags);
	cs3_shadow |= value;
	__simpad_write_cs3();
	spin_unlock_irqrestore(&cs3_lock, flags);
}