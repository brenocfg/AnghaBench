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
 scalar_t__ round (int,size_t) ; 
 void* xmalloc (int) ; 

void *
malloc_aligned(size_t size, size_t align)
{
	void *mem, *res;

	if (align < sizeof(void *))
		align = sizeof(void *);

	mem = xmalloc(size + sizeof(void *) + align - 1);
	res = (void *)round((uintptr_t)mem + sizeof(void *), align);
	*(void **)((uintptr_t)res - sizeof(void *)) = mem;
	return (res);
}