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
struct kevent {int dummy; } ;
typedef  int /*<<< orphan*/  ncpus ;
typedef  int /*<<< orphan*/  intmax_t ;
typedef  int /*<<< orphan*/  cpu_set_t ;
struct TYPE_2__ {int /*<<< orphan*/  sin_port; } ;

/* Variables and functions */
 int /*<<< orphan*/  CPU_SET (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CPU_SETSIZE ; 
 int /*<<< orphan*/  CPU_ZERO (int /*<<< orphan*/ *) ; 
 scalar_t__ Pflag ; 
 int /*<<< orphan*/  SYSCTLNAME_CPUS ; 
 int /*<<< orphan*/  bzero (struct kevent*,int) ; 
 int /*<<< orphan*/  err (int,char*,...) ; 
 int /*<<< orphan*/  errx (int,char*,int,...) ; 
 scalar_t__ finished ; 
 int /*<<< orphan*/  htons (scalar_t__) ; 
 int kevent (scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct kevent*,int,int /*<<< orphan*/ *) ; 
 scalar_t__ kq ; 
 scalar_t__ kqueue () ; 
 struct kevent* malloc (int) ; 
 int mflag ; 
 TYPE_1__ remoteip ; 
 scalar_t__ rflag ; 
 scalar_t__ sched_setaffinity (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  setproctitle (char*,int) ; 
 scalar_t__ started ; 
 scalar_t__ sysctlbyname (int /*<<< orphan*/ ,int*,size_t*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tcpp_client_handleconn (struct kevent*) ; 
 int /*<<< orphan*/  tcpp_client_newconn () ; 
 scalar_t__ tflag ; 

__attribute__((used)) static void
tcpp_client_worker(int workernum)
{
	struct kevent *kev_array;
	int i, numevents, kev_bytes;
#if defined(CPU_SETSIZE) && 0
	cpu_set_t mask;
	int ncpus;
	size_t len;

	if (Pflag) {
		len = sizeof(ncpus);
		if (sysctlbyname(SYSCTLNAME_CPUS, &ncpus, &len, NULL, 0) < 0)
			err(-1, "sysctlbyname: %s", SYSCTLNAME_CPUS);
		if (len != sizeof(ncpus))
			errx(-1, "sysctlbyname: %s: len %jd", SYSCTLNAME_CPUS,
			    (intmax_t)len);

		CPU_ZERO(&mask);
		CPU_SET(workernum % ncpus, &mask);
		if (sched_setaffinity(0, CPU_SETSIZE, &mask) < 0)
			err(-1, "sched_setaffinity");
	}
#endif
	setproctitle("tcpp_client %d", workernum);

	/*
	 * Add the worker number to the remote port.
	 */
	remoteip.sin_port = htons(rflag + workernum);

	kev_bytes = sizeof(*kev_array) * mflag;
	kev_array = malloc(kev_bytes);
	if (kev_array == NULL)
		err(-1, "malloc");
	bzero(kev_array, kev_bytes);

	kq = kqueue();
	if (kq < 0)
		err(-1, "kqueue");

	while (finished < tflag) {
		while ((started - finished < mflag) && (started < tflag))
			(void)tcpp_client_newconn();
		numevents = kevent(kq, NULL, 0, kev_array, mflag, NULL);
		if (numevents < 0)
			err(-1, "kevent");
		if (numevents > mflag)
			errx(-1, "kevent: %d", numevents);
		for (i = 0; i < numevents; i++)
			tcpp_client_handleconn(&kev_array[i]);
	}
	/* printf("Worker %d done - %d finished\n", workernum, finished); */
}