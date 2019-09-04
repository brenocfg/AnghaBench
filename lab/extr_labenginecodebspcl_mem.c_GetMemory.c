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
 int /*<<< orphan*/  Error (char*) ; 
 scalar_t__ MemorySize (void*) ; 
 int /*<<< orphan*/  allocedmemory ; 
 void* malloc (unsigned long) ; 

void *GetMemory(unsigned long size)
{
	void *ptr;
	ptr = malloc(size);
	if (!ptr) Error("out of memory");
	allocedmemory += MemorySize(ptr);
	return ptr;
}