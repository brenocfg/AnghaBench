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
typedef  unsigned long u_long ;
typedef  int /*<<< orphan*/  maxcpu ;

/* Variables and functions */
 int CPUSTATES ; 
 int /*<<< orphan*/ * kd ; 
 long* malloc (size_t) ; 
 int /*<<< orphan*/  mysysctl (char*,...) ; 
 int /*<<< orphan*/  xo_err (int,char*,size_t) ; 
 int /*<<< orphan*/  xo_errx (int,char*) ; 

__attribute__((used)) static int
getcpuinfo(u_long *maskp, int *maxidp)
{
	long *times;
	u_long mask;
	size_t size;
	int empty, i, j, maxcpu, maxid, ncpus;

	if (kd != NULL)
		xo_errx(1, "not implemented");
	mask = 0;
	ncpus = 0;
	size = sizeof(maxcpu);
	mysysctl("kern.smp.maxcpus", &maxcpu, &size);
	if (size != sizeof(maxcpu))
		xo_errx(1, "sysctl kern.smp.maxcpus");
	size = sizeof(long) * maxcpu * CPUSTATES;
	times = malloc(size);
	if (times == NULL)
		xo_err(1, "malloc %zd bytes", size);
	mysysctl("kern.cp_times", times, &size);
	maxid = (size / CPUSTATES / sizeof(long)) - 1;
	for (i = 0; i <= maxid; i++) {
		empty = 1;
		for (j = 0; empty && j < CPUSTATES; j++) {
			if (times[i * CPUSTATES + j] != 0)
				empty = 0;
		}
		if (!empty) {
			mask |= (1ul << i);
			ncpus++;
		}
	}
	if (maskp)
		*maskp = mask;
	if (maxidp)
		*maxidp = maxid;
	return (ncpus);
}