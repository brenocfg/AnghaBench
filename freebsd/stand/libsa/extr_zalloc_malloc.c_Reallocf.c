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
 int /*<<< orphan*/  Free (void*,char const*,int) ; 
 void* Realloc (void*,size_t,char const*,int) ; 

void *
Reallocf(void *ptr, size_t size, const char *file, int line)
{
	void *res;

	if ((res = Realloc(ptr, size, file, line)) == NULL)
		Free(ptr, file, line);
	return (res);
}