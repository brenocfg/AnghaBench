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
struct consdev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  alt_break_state ; 
 scalar_t__ kdb_active ; 
 int /*<<< orphan*/  kdb_alt_break (int,int /*<<< orphan*/ *) ; 
 int sbi_console_getchar () ; 

__attribute__((used)) static int
riscv_cngetc(struct consdev *cp)
{
	int ch;

#if defined(KDB)
	/*
	 * RISCVTODO: BBL polls for console data on timer interrupt,
	 * but interrupts are turned off in KDB.
	 * So we currently do not have console in KDB.
	 */
	if (kdb_active) {
		ch = sbi_console_getchar();
		while (ch) {
			ch = sbi_console_getchar();
		}
	}
#endif

	ch = sbi_console_getchar();
	if (ch > 0 && ch < 0xff) {
#if defined(KDB)
		kdb_alt_break(ch, &alt_break_state);
#endif
		return (ch);
	}

	return (-1);
}