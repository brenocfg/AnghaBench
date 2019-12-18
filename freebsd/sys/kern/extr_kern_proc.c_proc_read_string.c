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
typedef  int /*<<< orphan*/  vm_offset_t ;
struct thread {int dummy; } ;
struct proc {int dummy; } ;
typedef  scalar_t__ ssize_t ;

/* Variables and functions */
 int ENOMEM ; 
 scalar_t__ proc_readmem (struct thread*,struct proc*,int /*<<< orphan*/ ,char*,size_t) ; 

__attribute__((used)) static int
proc_read_string(struct thread *td, struct proc *p, const char *sptr, char *buf,
    size_t len)
{
	ssize_t n;

	/*
	 * This may return a short read if the string is shorter than the chunk
	 * and is aligned at the end of the page, and the following page is not
	 * mapped.
	 */
	n = proc_readmem(td, p, (vm_offset_t)sptr, buf, len);
	if (n <= 0)
		return (ENOMEM);
	return (0);
}