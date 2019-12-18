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
 int NMI_DONE ; 
 int NMI_HANDLED ; 
#define  NMI_LOCAL 129 
#define  NMI_UNKNOWN 128 
 int /*<<< orphan*/  __test_and_clear_bit (int,int /*<<< orphan*/ ) ; 
 int atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kgdb_active ; 
 int /*<<< orphan*/  kgdb_nmicallback (int,struct pt_regs*) ; 
 int raw_smp_processor_id () ; 
 int /*<<< orphan*/  set_bit (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  touch_nmi_watchdog () ; 
 int /*<<< orphan*/  was_in_debug_nmi ; 

__attribute__((used)) static int kgdb_nmi_handler(unsigned int cmd, struct pt_regs *regs)
{
	int cpu;

	switch (cmd) {
	case NMI_LOCAL:
		if (atomic_read(&kgdb_active) != -1) {
			/* KGDB CPU roundup */
			cpu = raw_smp_processor_id();
			kgdb_nmicallback(cpu, regs);
			set_bit(cpu, was_in_debug_nmi);
			touch_nmi_watchdog();

			return NMI_HANDLED;
		}
		break;

	case NMI_UNKNOWN:
		cpu = raw_smp_processor_id();

		if (__test_and_clear_bit(cpu, was_in_debug_nmi))
			return NMI_HANDLED;

		break;
	default:
		/* do nothing */
		break;
	}
	return NMI_DONE;
}