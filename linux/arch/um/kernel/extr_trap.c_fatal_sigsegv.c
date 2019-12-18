#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  regs; } ;
struct TYPE_4__ {TYPE_1__ thread; } ;

/* Variables and functions */
 int /*<<< orphan*/  SIGSEGV ; 
 TYPE_2__* current ; 
 int /*<<< orphan*/  do_signal (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  force_sigsegv (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  os_dump_core () ; 

void fatal_sigsegv(void)
{
	force_sigsegv(SIGSEGV);
	do_signal(&current->thread.regs);
	/*
	 * This is to tell gcc that we're not returning - do_signal
	 * can, in general, return, but in this case, it's not, since
	 * we just got a fatal SIGSEGV queued.
	 */
	os_dump_core();
}