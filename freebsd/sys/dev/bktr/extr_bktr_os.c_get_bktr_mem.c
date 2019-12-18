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
typedef  scalar_t__ vm_offset_t ;

/* Variables and functions */
 int /*<<< orphan*/  M_DEVBUF ; 
 int /*<<< orphan*/  M_NOWAIT ; 
 int PAGE_SIZE ; 
 scalar_t__ contigmalloc (unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,int,unsigned int) ; 

vm_offset_t
get_bktr_mem( int unit, unsigned size )
{
	vm_offset_t	addr = 0;

	addr = (vm_offset_t)contigmalloc(size, M_DEVBUF, M_NOWAIT, 0,
	    0xffffffff, 1<<24, 0);
	if (addr == 0)
		addr = (vm_offset_t)contigmalloc(size, M_DEVBUF, M_NOWAIT, 0,
		    0xffffffff, PAGE_SIZE, 0);
	if (addr == 0) {
		printf("bktr%d: Unable to allocate %d bytes of memory.\n",
			unit, size);
	}

	return( addr );
}