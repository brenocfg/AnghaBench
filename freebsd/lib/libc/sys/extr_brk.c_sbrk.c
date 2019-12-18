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
 scalar_t__ curbrk ; 
 int /*<<< orphan*/  errno ; 
 int initbrk () ; 
 void* mvbrk (void*) ; 

void *
sbrk(intptr_t incr)
{

	if (initbrk() == -1)
		return ((void *)-1);
	if ((incr > 0 && curbrk + incr < curbrk) ||
	    (incr < 0 && curbrk + incr > curbrk)) {
		/* Emulate legacy error handling in the syscall. */
		errno = EINVAL;
		return ((void *)-1);
	}
	return (mvbrk((void *)(curbrk + incr)));
}