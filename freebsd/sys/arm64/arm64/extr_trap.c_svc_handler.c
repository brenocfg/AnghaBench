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
struct trapframe {int tf_esr; scalar_t__ tf_elr; } ;
struct thread {int dummy; } ;

/* Variables and functions */
 int ESR_ELx_ISS_MASK ; 
 int /*<<< orphan*/  ILL_ILLOPN ; 
 int /*<<< orphan*/  SIGILL ; 
 int /*<<< orphan*/  call_trapsignal (struct thread*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  syscallenter (struct thread*) ; 
 int /*<<< orphan*/  syscallret (struct thread*) ; 
 int /*<<< orphan*/  userret (struct thread*,struct trapframe*) ; 

__attribute__((used)) static void
svc_handler(struct thread *td, struct trapframe *frame)
{

	if ((frame->tf_esr & ESR_ELx_ISS_MASK) == 0) {
		syscallenter(td);
		syscallret(td);
	} else {
		call_trapsignal(td, SIGILL, ILL_ILLOPN, (void *)frame->tf_elr);
		userret(td, frame);
	}
}