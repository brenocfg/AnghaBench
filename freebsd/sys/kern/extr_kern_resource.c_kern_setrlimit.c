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
typedef  int /*<<< orphan*/  u_int ;
struct thread {int /*<<< orphan*/  td_proc; } ;
struct rlimit {int dummy; } ;

/* Variables and functions */
 int kern_proc_setrlimit (struct thread*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct rlimit*) ; 

int
kern_setrlimit(struct thread *td, u_int which, struct rlimit *limp)
{

	return (kern_proc_setrlimit(td, td->td_proc, which, limp));
}