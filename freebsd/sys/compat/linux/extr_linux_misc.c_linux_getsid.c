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
struct linux_getsid_args {int /*<<< orphan*/  pid; } ;
struct getsid_args {int /*<<< orphan*/  pid; } ;

/* Variables and functions */
 int sys_getsid (struct thread*,struct getsid_args*) ; 

int
linux_getsid(struct thread *td, struct linux_getsid_args *args)
{
	struct getsid_args bsd;

	bsd.pid = args->pid;
	return (sys_getsid(td, &bsd));
}