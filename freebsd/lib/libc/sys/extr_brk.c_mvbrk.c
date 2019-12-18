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

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 void* __sys_break (void*) ; 
 uintptr_t curbrk ; 
 int /*<<< orphan*/  errno ; 
 uintptr_t minbrk ; 

__attribute__((used)) static void *
mvbrk(void *addr)
{
	uintptr_t oldbrk;

	if ((uintptr_t)addr < minbrk) {
		/* Emulate legacy error handling in the syscall. */
		errno = EINVAL;
		return ((void *)-1);
	}
	if (__sys_break(addr) == (void *)-1)
		return ((void *)-1);
	oldbrk = curbrk;
	curbrk = (uintptr_t)addr;
	return ((void *)oldbrk);
}