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
 int /*<<< orphan*/  _machine_halt () ; 
 int /*<<< orphan*/  local_irq_disable () ; 
 int /*<<< orphan*/  rbtx4938_sfvol_addr ; 
 int /*<<< orphan*/  rbtx4938_softreset_addr ; 
 int /*<<< orphan*/  rbtx4938_softresetlock_addr ; 
 int /*<<< orphan*/  stub1 () ; 
 int /*<<< orphan*/  writeb (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void rbtx4938_machine_restart(char *command)
{
	local_irq_disable();
	writeb(1, rbtx4938_softresetlock_addr);
	writeb(1, rbtx4938_sfvol_addr);
	writeb(1, rbtx4938_softreset_addr);
	/* fallback */
	(*_machine_halt)();
}