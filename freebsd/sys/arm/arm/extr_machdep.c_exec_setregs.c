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
struct trapframe {int tf_svc_lr; int /*<<< orphan*/  tf_spsr; int /*<<< orphan*/  tf_pc; int /*<<< orphan*/  tf_usr_lr; int /*<<< orphan*/  tf_usr_sp; } ;
struct thread {struct trapframe* td_frame; } ;
struct image_params {int /*<<< orphan*/  entry_addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  PSR_USR32_MODE ; 
 int /*<<< orphan*/  memset (struct trapframe*,int /*<<< orphan*/ ,int) ; 

void
exec_setregs(struct thread *td, struct image_params *imgp, u_long stack)
{
	struct trapframe *tf = td->td_frame;

	memset(tf, 0, sizeof(*tf));
	tf->tf_usr_sp = stack;
	tf->tf_usr_lr = imgp->entry_addr;
	tf->tf_svc_lr = 0x77777777;
	tf->tf_pc = imgp->entry_addr;
	tf->tf_spsr = PSR_USR32_MODE;
}