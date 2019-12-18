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
 int /*<<< orphan*/  fatal (char*,size_t,size_t) ; 
 void* recallocarray (void*,size_t,size_t,size_t) ; 

void *
xrecallocarray(void *ptr, size_t onmemb, size_t nmemb, size_t size)
{
	void *new_ptr;

	new_ptr = recallocarray(ptr, onmemb, nmemb, size);
	if (new_ptr == NULL)
		fatal("xrecallocarray: out of memory (%zu elements of %zu bytes)",
		    nmemb, size);
	return new_ptr;
}