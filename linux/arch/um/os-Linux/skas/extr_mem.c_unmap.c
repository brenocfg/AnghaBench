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
struct mm_id {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  __NR_munmap ; 
 int run_syscall_stub (struct mm_id*,int /*<<< orphan*/ ,unsigned long*,int /*<<< orphan*/ ,void**,int) ; 

int unmap(struct mm_id * mm_idp, unsigned long addr, unsigned long len,
	  int done, void **data)
{
	int ret;
	unsigned long args[] = { (unsigned long) addr, len, 0, 0, 0,
				 0 };

	ret = run_syscall_stub(mm_idp, __NR_munmap, args, 0,
			       data, done);

	return ret;
}