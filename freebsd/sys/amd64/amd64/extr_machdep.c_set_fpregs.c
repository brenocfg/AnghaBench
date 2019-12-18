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
struct thread {int dummy; } ;
struct fpreg {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  critical_enter () ; 
 int /*<<< orphan*/  critical_exit () ; 
 int /*<<< orphan*/  fpuuserinited (struct thread*) ; 
 int /*<<< orphan*/  get_pcb_user_save_td (struct thread*) ; 
 int /*<<< orphan*/  set_fpregs_xmm (struct fpreg*,int /*<<< orphan*/ ) ; 

int
set_fpregs(struct thread *td, struct fpreg *fpregs)
{

	critical_enter();
	set_fpregs_xmm(fpregs, get_pcb_user_save_td(td));
	fpuuserinited(td);
	critical_exit();
	return (0);
}