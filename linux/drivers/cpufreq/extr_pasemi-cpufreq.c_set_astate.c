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
 scalar_t__ SDCASR_REG ; 
 int SDCASR_REG_STRIDE ; 
 int /*<<< orphan*/  local_irq_restore (unsigned long) ; 
 int /*<<< orphan*/  local_irq_save (unsigned long) ; 
 int /*<<< orphan*/  out_le32 (scalar_t__,unsigned int) ; 
 scalar_t__ sdcasr_mapbase ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static void set_astate(int cpu, unsigned int astate)
{
	unsigned long flags;

	/* Return if called before init has run */
	if (unlikely(!sdcasr_mapbase))
		return;

	local_irq_save(flags);

	out_le32(sdcasr_mapbase + SDCASR_REG + SDCASR_REG_STRIDE*cpu, astate);

	local_irq_restore(flags);
}