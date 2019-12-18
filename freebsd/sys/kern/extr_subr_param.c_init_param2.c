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
 int /*<<< orphan*/  MAXFILES ; 
 int MAXUSERS ; 
 long NBUF ; 
 long NPROC ; 
 int PAGE_SIZE ; 
 int /*<<< orphan*/  TUNABLE_INT_FETCH (char*,...) ; 
 int /*<<< orphan*/  TUNABLE_LONG_FETCH (char*,int*) ; 
 int VM_MAX_AUTOTUNE_MAXUSERS ; 
 int VM_MAX_KERNEL_ADDRESS ; 
 int VM_MIN_KERNEL_ADDRESS ; 
 long bio_transient_maxcnt ; 
 long imax (int /*<<< orphan*/ ,long) ; 
 long maxfiles ; 
 long maxfilesperproc ; 
 int maxpipekva ; 
 long maxproc ; 
 long maxprocperuid ; 
 int maxusers ; 
 long nbuf ; 
 long nswbuf ; 
 long pid_max ; 

void
init_param2(long physpages)
{

	/* Base parameters */
	maxusers = MAXUSERS;
	TUNABLE_INT_FETCH("kern.maxusers", &maxusers);
	if (maxusers == 0) {
		maxusers = physpages / (2 * 1024 * 1024 / PAGE_SIZE);
		if (maxusers < 32)
			maxusers = 32;
#ifdef VM_MAX_AUTOTUNE_MAXUSERS
                if (maxusers > VM_MAX_AUTOTUNE_MAXUSERS)
                        maxusers = VM_MAX_AUTOTUNE_MAXUSERS;
#endif
                /*
                 * Scales down the function in which maxusers grows once
                 * we hit 384.
                 */
                if (maxusers > 384)
                        maxusers = 384 + ((maxusers - 384) / 8);
        }

	/*
	 * The following can be overridden after boot via sysctl.  Note:
	 * unless overriden, these macros are ultimately based on maxusers.
	 * Limit maxproc so that kmap entries cannot be exhausted by
	 * processes.
	 */
	maxproc = NPROC;
	TUNABLE_INT_FETCH("kern.maxproc", &maxproc);
	if (maxproc > (physpages / 12))
		maxproc = physpages / 12;
	if (maxproc > pid_max)
		maxproc = pid_max;
	maxprocperuid = (maxproc * 9) / 10;

	/*
	 * The default limit for maxfiles is 1/12 of the number of
	 * physical page but not less than 16 times maxusers.
	 * At most it can be 1/6 the number of physical pages.
	 */
	maxfiles = imax(MAXFILES, physpages / 8);
	TUNABLE_INT_FETCH("kern.maxfiles", &maxfiles);
	if (maxfiles > (physpages / 4))
		maxfiles = physpages / 4;
	maxfilesperproc = (maxfiles / 10) * 9;
	TUNABLE_INT_FETCH("kern.maxfilesperproc", &maxfilesperproc);

	/*
	 * Cannot be changed after boot.
	 */
	nbuf = NBUF;
	TUNABLE_INT_FETCH("kern.nbuf", &nbuf);
	TUNABLE_INT_FETCH("kern.bio_transient_maxcnt", &bio_transient_maxcnt);

	/*
	 * Physical buffers are pre-allocated buffers (struct buf) that
	 * are used as temporary holders for I/O, such as paging I/O.
	 */
	TUNABLE_INT_FETCH("kern.nswbuf", &nswbuf);

	/*
	 * The default for maxpipekva is min(1/64 of the kernel address space,
	 * max(1/64 of main memory, 512KB)).  See sys_pipe.c for more details.
	 */
	maxpipekva = (physpages / 64) * PAGE_SIZE;
	TUNABLE_LONG_FETCH("kern.ipc.maxpipekva", &maxpipekva);
	if (maxpipekva < 512 * 1024)
		maxpipekva = 512 * 1024;
	if (maxpipekva > (VM_MAX_KERNEL_ADDRESS - VM_MIN_KERNEL_ADDRESS) / 64)
		maxpipekva = (VM_MAX_KERNEL_ADDRESS - VM_MIN_KERNEL_ADDRESS) /
		    64;
}