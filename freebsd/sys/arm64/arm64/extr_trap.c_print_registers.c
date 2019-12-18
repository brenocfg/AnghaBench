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
struct trapframe {int tf_sp; int tf_lr; int tf_elr; int tf_spsr; int /*<<< orphan*/ * tf_x; } ;

/* Variables and functions */
 int nitems (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  printf (char*,...) ; 

__attribute__((used)) static void
print_registers(struct trapframe *frame)
{
	u_int reg;

	for (reg = 0; reg < nitems(frame->tf_x); reg++) {
		printf(" %sx%d: %16lx\n", (reg < 10) ? " " : "", reg,
		    frame->tf_x[reg]);
	}
	printf("  sp: %16lx\n", frame->tf_sp);
	printf("  lr: %16lx\n", frame->tf_lr);
	printf(" elr: %16lx\n", frame->tf_elr);
	printf("spsr:         %8x\n", frame->tf_spsr);
}