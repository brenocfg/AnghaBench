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
 int RB_HALT ; 
 int /*<<< orphan*/  WD_TO_NEVER ; 
 int cngetc () ; 
 int /*<<< orphan*/  cpu_halt () ; 
 int /*<<< orphan*/  printf (char*) ; 
 int /*<<< orphan*/  wdog_kern_pat (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
shutdown_halt(void *junk, int howto)
{

	if (howto & RB_HALT) {
		printf("\n");
		printf("The operating system has halted.\n");
		printf("Please press any key to reboot.\n\n");

		wdog_kern_pat(WD_TO_NEVER);

		switch (cngetc()) {
		case -1:		/* No console, just die */
			cpu_halt();
			/* NOTREACHED */
		default:
			break;
		}
	}
}