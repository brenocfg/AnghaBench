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
typedef  int /*<<< orphan*/  uint64_t ;
struct trapframe {int /*<<< orphan*/  tf_esr; } ;

/* Variables and functions */
 int /*<<< orphan*/  READ_SPECIALREG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  far_el1 ; 
 int /*<<< orphan*/  panic (char*) ; 
 int /*<<< orphan*/  print_registers (struct trapframe*) ; 
 int /*<<< orphan*/  printf (char*,int /*<<< orphan*/ ) ; 

void
unhandled_exception(struct trapframe *frame)
{
	uint64_t esr, far;

	far = READ_SPECIALREG(far_el1);
	esr = frame->tf_esr;

	print_registers(frame);
	printf(" far: %16lx\n", far);
	printf(" esr:         %.8lx\n", esr);
	panic("Unhandled exception");
}