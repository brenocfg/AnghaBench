#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u_long ;
struct thread {int dummy; } ;
struct TYPE_4__ {int ksi_signo; int ksi_code; } ;
typedef  TYPE_1__ ksiginfo_t ;

/* Variables and functions */
 int /*<<< orphan*/  ksiginfo_init_trap (TYPE_1__*) ; 
 int /*<<< orphan*/  trapsignal (struct thread*,TYPE_1__*) ; 

__attribute__((used)) static __inline void
call_trapsignal(struct thread *td, int sig, u_long code)
{
	ksiginfo_t ksi;

	ksiginfo_init_trap(&ksi);
	ksi.ksi_signo = sig;
	ksi.ksi_code = (int)code;
	trapsignal(td, &ksi);
}