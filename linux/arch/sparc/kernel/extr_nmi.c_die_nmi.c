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
struct pt_regs {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DIE_NMIWATCHDOG ; 
 scalar_t__ NOTIFY_STOP ; 
 int /*<<< orphan*/  SIGINT ; 
 int /*<<< orphan*/  WARN (int,char*,int) ; 
 scalar_t__ notify_die (int /*<<< orphan*/ ,char const*,struct pt_regs*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  panic (char*,int) ; 
 scalar_t__ panic_on_oops ; 
 int /*<<< orphan*/  pt_regs_trap_type (struct pt_regs*) ; 
 int smp_processor_id () ; 

__attribute__((used)) static void die_nmi(const char *str, struct pt_regs *regs, int do_panic)
{
	int this_cpu = smp_processor_id();

	if (notify_die(DIE_NMIWATCHDOG, str, regs, 0,
		       pt_regs_trap_type(regs), SIGINT) == NOTIFY_STOP)
		return;

	if (do_panic || panic_on_oops)
		panic("Watchdog detected hard LOCKUP on cpu %d", this_cpu);
	else
		WARN(1, "Watchdog detected hard LOCKUP on cpu %d", this_cpu);
}