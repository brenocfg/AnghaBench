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
typedef  int u_int ;
typedef  int /*<<< orphan*/  register_t ;

/* Variables and functions */
 int /*<<< orphan*/  do_cpuid (int,int*) ; 
 int /*<<< orphan*/  intr_disable () ; 
 int /*<<< orphan*/  intr_restore (int /*<<< orphan*/ ) ; 

__attribute__((used)) static u_int
tmx86_get_longrun_status(u_int * frequency, u_int * voltage, u_int * percentage)
{
	register_t	saveintr;
	u_int		regs[4];

	saveintr = intr_disable();

	do_cpuid(0x80860007, regs);
	*frequency = regs[0];
	*voltage = regs[1];
	*percentage = regs[2];

	intr_restore(saveintr);
	return (1);
}