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
 scalar_t__ ALCHEMY_CPU_AU1300 ; 
 int /*<<< orphan*/  __disable_block (int) ; 
 int /*<<< orphan*/  __enable_block (int) ; 
 scalar_t__ alchemy_get_cputype () ; 
 int /*<<< orphan*/  au1300_vss_lock ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

void au1300_vss_block_control(int block, int enable)
{
	unsigned long flags;

	if (alchemy_get_cputype() != ALCHEMY_CPU_AU1300)
		return;

	/* only one block at a time */
	spin_lock_irqsave(&au1300_vss_lock, flags);
	if (enable)
		__enable_block(block);
	else
		__disable_block(block);
	spin_unlock_irqrestore(&au1300_vss_lock, flags);
}