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
 int /*<<< orphan*/  M_DEVBUF ; 
 int /*<<< orphan*/  M_NOWAIT ; 
 int /*<<< orphan*/  M_WAITOK ; 
 int VMCI_MEMORY_ATOMIC ; 
 void* contigmalloc (size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int) ; 

void *
vmci_alloc_kernel_mem(size_t size, int flags)
{
	void *ptr;

	if ((flags & VMCI_MEMORY_ATOMIC) != 0)
		ptr = contigmalloc(size, M_DEVBUF, M_NOWAIT, 0, 0xFFFFFFFF,
		    8, 1024 * 1024);
	else
		ptr = contigmalloc(size, M_DEVBUF, M_WAITOK, 0, 0xFFFFFFFF,
		    8, 1024 * 1024);

	return (ptr);
}