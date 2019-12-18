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
 void* __sys_break (int /*<<< orphan*/ *) ; 
 uintptr_t curbrk ; 
 int curbrk_initted ; 
 uintptr_t minbrk ; 

__attribute__((used)) static int
initbrk(void)
{
	void *newbrk;

	if (!curbrk_initted) {
		newbrk = __sys_break(NULL);
		if (newbrk == (void *)-1)
			return (-1);
		curbrk = minbrk = (uintptr_t)newbrk;
		curbrk_initted = 1;
	}
	return (0);
}