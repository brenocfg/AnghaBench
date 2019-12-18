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
 int /*<<< orphan*/  die (char*) ; 
 int /*<<< orphan*/  memory_limit_check (size_t,int /*<<< orphan*/ ) ; 
 void* realloc (void*,int) ; 

void *xrealloc(void *ptr, size_t size)
{
	void *ret;

	memory_limit_check(size, 0);
	ret = realloc(ptr, size);
	if (!ret && !size)
		ret = realloc(ptr, 1);
	if (!ret)
		die("Out of memory, realloc failed");
	return ret;
}