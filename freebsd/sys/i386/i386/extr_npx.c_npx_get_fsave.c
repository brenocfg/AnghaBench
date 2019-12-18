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
union savefpu {int /*<<< orphan*/  sv_xmm; } ;
struct thread {int dummy; } ;
struct fpacc87 {int dummy; } ;
struct env87 {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  bcopy (union savefpu*,void*,int) ; 
 scalar_t__ cpu_fxsr ; 
 struct thread* curthread ; 
 union savefpu* get_pcb_user_save_td (struct thread*) ; 
 int /*<<< orphan*/  npx_fill_fpregs_xmm1 (int /*<<< orphan*/ *,void*) ; 
 int /*<<< orphan*/  npxgetregs (struct thread*) ; 

void
npx_get_fsave(void *addr)
{
	struct thread *td;
	union savefpu *sv;

	td = curthread;
	npxgetregs(td);
	sv = get_pcb_user_save_td(td);
	if (cpu_fxsr)
		npx_fill_fpregs_xmm1(&sv->sv_xmm, addr);
	else
		bcopy(sv, addr, sizeof(struct env87) +
		    sizeof(struct fpacc87[8]));
}