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
struct trapframe {int dummy; } ;
struct thread {struct trapframe* td_frame; } ;

/* Variables and functions */
 struct thread* curthread ; 
 int /*<<< orphan*/  syscallenter (struct thread*) ; 
 int /*<<< orphan*/  syscallret (struct thread*) ; 

__attribute__((used)) static void
svc_handler(struct trapframe *frame)
{
	struct thread *td;

	td = curthread;
	td->td_frame = frame;

	syscallenter(td);
	syscallret(td);
}