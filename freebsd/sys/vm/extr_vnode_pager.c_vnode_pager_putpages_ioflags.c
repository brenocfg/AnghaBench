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
 int IO_ASYNC ; 
 int IO_INVAL ; 
 int IO_NOREUSE ; 
 int IO_SEQMAX ; 
 int IO_SEQSHIFT ; 
 int IO_SYNC ; 
 int IO_VMIO ; 
 int VM_PAGER_CLUSTER_OK ; 
 int VM_PAGER_PUT_INVAL ; 
 int VM_PAGER_PUT_NOREUSE ; 
 int VM_PAGER_PUT_SYNC ; 

int
vnode_pager_putpages_ioflags(int pager_flags)
{
	int ioflags;

	/*
	 * Pageouts are already clustered, use IO_ASYNC to force a
	 * bawrite() rather then a bdwrite() to prevent paging I/O
	 * from saturating the buffer cache.  Dummy-up the sequential
	 * heuristic to cause large ranges to cluster.  If neither
	 * IO_SYNC or IO_ASYNC is set, the system decides how to
	 * cluster.
	 */
	ioflags = IO_VMIO;
	if ((pager_flags & (VM_PAGER_PUT_SYNC | VM_PAGER_PUT_INVAL)) != 0)
		ioflags |= IO_SYNC;
	else if ((pager_flags & VM_PAGER_CLUSTER_OK) == 0)
		ioflags |= IO_ASYNC;
	ioflags |= (pager_flags & VM_PAGER_PUT_INVAL) != 0 ? IO_INVAL: 0;
	ioflags |= (pager_flags & VM_PAGER_PUT_NOREUSE) != 0 ? IO_NOREUSE : 0;
	ioflags |= IO_SEQMAX << IO_SEQSHIFT;
	return (ioflags);
}