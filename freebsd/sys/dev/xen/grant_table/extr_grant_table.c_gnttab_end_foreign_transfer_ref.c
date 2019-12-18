#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int uint16_t ;
typedef  size_t grant_ref_t ;
struct TYPE_2__ {int flags; unsigned long frame; } ;

/* Variables and functions */
 int GTF_transfer_committed ; 
 int GTF_transfer_completed ; 
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int /*<<< orphan*/  cpu_spinwait () ; 
 int /*<<< orphan*/  rmb () ; 
 TYPE_1__* shared ; 
 int synch_cmpxchg (int*,int,int /*<<< orphan*/ ) ; 

unsigned long
gnttab_end_foreign_transfer_ref(grant_ref_t ref)
{
	unsigned long frame;
	uint16_t      flags;

	/*
         * If a transfer is not even yet started, try to reclaim the grant
         * reference and return failure (== 0).
         */
	while (!((flags = shared[ref].flags) & GTF_transfer_committed)) {
		if ( synch_cmpxchg(&shared[ref].flags, flags, 0) == flags )
			return (0);
		cpu_spinwait();
	}

	/* If a transfer is in progress then wait until it is completed. */
	while (!(flags & GTF_transfer_completed)) {
		flags = shared[ref].flags;
		cpu_spinwait();
	}

	/* Read the frame number /after/ reading completion status. */
	rmb();
	frame = shared[ref].frame;
	KASSERT(frame != 0, ("grant table inconsistent"));

	return (frame);
}