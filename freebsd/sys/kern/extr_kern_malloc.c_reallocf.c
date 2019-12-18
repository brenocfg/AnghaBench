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
struct malloc_type {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (void*,struct malloc_type*) ; 
 void* realloc (void*,size_t,struct malloc_type*,int) ; 

void *
reallocf(void *addr, size_t size, struct malloc_type *mtp, int flags)
{
	void *mem;

	if ((mem = realloc(addr, size, mtp, flags)) == NULL)
		free(addr, mtp);
	return (mem);
}