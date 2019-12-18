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
struct thread {int /*<<< orphan*/  td_proc; } ;

/* Variables and functions */
 int EFAULT ; 
 int proc_readmem (struct thread*,int /*<<< orphan*/ ,uintptr_t,int*,int) ; 

__attribute__((used)) static int
ptrace_read_int(struct thread *td, uintptr_t addr, int *v)
{

	if (proc_readmem(td, td->td_proc, addr, v, sizeof(*v)) != sizeof(*v))
		return (EFAULT);
	return (0);
}