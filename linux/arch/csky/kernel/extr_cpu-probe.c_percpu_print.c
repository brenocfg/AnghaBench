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
struct seq_file {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CSKYCPU_DEF_NAME ; 
 int mfcr (char*) ; 
 int /*<<< orphan*/  mfcr_ccr2 () ; 
 int /*<<< orphan*/  mfcr_hint () ; 
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,...) ; 
 int /*<<< orphan*/  smp_processor_id () ; 

__attribute__((used)) static void percpu_print(void *arg)
{
	struct seq_file *m = (struct seq_file *)arg;
	unsigned int cur, next, i;

	seq_printf(m, "processor       : %d\n", smp_processor_id());
	seq_printf(m, "C-SKY CPU model : %s\n", CSKYCPU_DEF_NAME);

	/* read processor id, max is 100 */
	cur  = mfcr("cr13");
	for (i = 0; i < 100; i++) {
		seq_printf(m, "product info[%d] : 0x%08x\n", i, cur);

		next = mfcr("cr13");

		/* some CPU only has one id reg */
		if (cur == next)
			break;

		cur = next;

		/* cpid index is 31-28, reset */
		if (!(next >> 28)) {
			while ((mfcr("cr13") >> 28) != i);
			break;
		}
	}

	/* CPU feature regs, setup by bootloader or gdbinit */
	seq_printf(m, "hint (CPU funcs): 0x%08x\n", mfcr_hint());
	seq_printf(m, "ccr  (L1C & MMU): 0x%08x\n", mfcr("cr18"));
	seq_printf(m, "ccr2 (L2C)      : 0x%08x\n", mfcr_ccr2());
	seq_printf(m, "\n");
}