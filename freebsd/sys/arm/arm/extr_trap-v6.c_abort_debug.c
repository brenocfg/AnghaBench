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
typedef  scalar_t__ u_int ;
struct trapframe {int dummy; } ;
struct thread {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  SIGTRAP ; 
 int /*<<< orphan*/  TRAP_BRKPT ; 
 int /*<<< orphan*/  T_BREAKPOINT ; 
 int /*<<< orphan*/  T_WATCHPOINT ; 
 int /*<<< orphan*/  call_trapsignal (struct thread*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 struct thread* curthread ; 
 int /*<<< orphan*/  kdb_trap (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct trapframe*) ; 
 int /*<<< orphan*/  printf (char*) ; 
 int /*<<< orphan*/  userret (struct thread*,struct trapframe*) ; 

__attribute__((used)) static __inline void
abort_debug(struct trapframe *tf, u_int fsr, u_int prefetch, bool usermode,
    u_int far)
{

	if (usermode) {
		struct thread *td;

		td = curthread;
		call_trapsignal(td, SIGTRAP, TRAP_BRKPT, far);
		userret(td, tf);
	} else {
#ifdef KDB
		kdb_trap((prefetch) ? T_BREAKPOINT : T_WATCHPOINT, 0, tf);
#else
		printf("No debugger in kernel.\n");
#endif
	}
}