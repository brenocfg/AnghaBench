#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct trapframe {int dummy; } ;
struct TYPE_2__ {int nap; } ;
struct thread {TYPE_1__ td_sa; } ;

/* Variables and functions */
 int /*<<< orphan*/  syscallenter (struct thread*) ; 
 int /*<<< orphan*/  syscallret (struct thread*) ; 

__attribute__((used)) static void
syscall(struct thread *td, struct trapframe *frame)
{

	td->td_sa.nap = 4;
	syscallenter(td);
	syscallret(td);
}