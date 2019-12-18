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
typedef  int /*<<< orphan*/  u_long ;
struct trapframe {int tf_lr; int tf_elr; int /*<<< orphan*/  tf_sp; } ;
struct thread {struct trapframe* td_frame; } ;
struct image_params {int entry_addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  LIN_SDT_PROBE0 (int /*<<< orphan*/ ,void (*) (struct thread*,struct image_params*,int /*<<< orphan*/ ),int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct trapframe*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sysvec ; 
 int /*<<< orphan*/  todo ; 

__attribute__((used)) static void
linux_exec_setregs(struct thread *td, struct image_params *imgp, u_long stack)
{
	struct trapframe *regs = td->td_frame;

	/* LINUXTODO: validate */
	LIN_SDT_PROBE0(sysvec, linux_exec_setregs, todo);

	memset(regs, 0, sizeof(*regs));
	/* glibc start.S registers function pointer in x0 with atexit. */
        regs->tf_sp = stack;
#if 0	/* LINUXTODO: See if this is used. */
	regs->tf_lr = imgp->entry_addr;
#else
        regs->tf_lr = 0xffffffffffffffff;
#endif
        regs->tf_elr = imgp->entry_addr;
}