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
 int /*<<< orphan*/  barrier () ; 
 scalar_t__ get_tb () ; 
 int /*<<< orphan*/  local_irq_restore (unsigned long) ; 
 int /*<<< orphan*/  local_irq_save (unsigned long) ; 
 int /*<<< orphan*/  mb () ; 
 int /*<<< orphan*/  pmac_tb_freeze (int) ; 
 int /*<<< orphan*/  stub1 (int) ; 
 int /*<<< orphan*/  stub2 (int) ; 
 scalar_t__ tb_req ; 
 scalar_t__ timebase ; 

__attribute__((used)) static void smp_core99_give_timebase(void)
{
	unsigned long flags;

	local_irq_save(flags);

	while(!tb_req)
		barrier();
	tb_req = 0;
	(*pmac_tb_freeze)(1);
	mb();
	timebase = get_tb();
	mb();
	while (timebase)
		barrier();
	mb();
	(*pmac_tb_freeze)(0);
	mb();

	local_irq_restore(flags);
}