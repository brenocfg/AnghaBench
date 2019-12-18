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
 int /*<<< orphan*/  INIT_JMP_REBOOT ; 
 int /*<<< orphan*/  UML_LONGJMP (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  block_signals_trace () ; 
 int /*<<< orphan*/  initial_jmpbuf ; 

void reboot_skas(void)
{
	block_signals_trace();
	UML_LONGJMP(&initial_jmpbuf, INIT_JMP_REBOOT);
}