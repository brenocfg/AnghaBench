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
typedef  int /*<<< orphan*/  pid_t ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  linux_msg (struct thread*,char*) ; 

__attribute__((used)) static int
linux_ptrace_peekuser(struct thread *td, pid_t pid, void *addr, void *data)
{

	linux_msg(td, "PTRACE_PEEKUSER not implemented; returning EINVAL");
	return (EINVAL);
}