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
struct timespec {int tv_sec; int tv_nsec; } ;
struct tcpp_header {int dummy; } ;
typedef  scalar_t__ pid_t ;
typedef  int /*<<< orphan*/  intmax_t ;
typedef  int /*<<< orphan*/  cp_time_start ;
typedef  int /*<<< orphan*/  cp_time_finish ;

/* Variables and functions */
 int /*<<< orphan*/  CLOCK_REALTIME ; 
 int CPUSTATES ; 
 size_t CP_IDLE ; 
 size_t CP_INTR ; 
 size_t CP_NICE ; 
 size_t CP_SYS ; 
 size_t CP_USER ; 
 int /*<<< orphan*/  SIGKILL ; 
 int /*<<< orphan*/  SYSCTLNAME_CPTIME ; 
 scalar_t__ WEXITSTATUS (int) ; 
 int bflag ; 
 int /*<<< orphan*/  bzero (scalar_t__*,int) ; 
 scalar_t__ clock_gettime (int /*<<< orphan*/ ,struct timespec*) ; 
 int /*<<< orphan*/  err (int,char*,...) ; 
 int /*<<< orphan*/  errx (int,char*,...) ; 
 int /*<<< orphan*/  exit (int) ; 
 scalar_t__ fork () ; 
 scalar_t__ hflag ; 
 int /*<<< orphan*/  kill (scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__* malloc (int) ; 
 int payload_len ; 
 int pflag ; 
 scalar_t__* pid_list ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 scalar_t__ sysctlbyname (int /*<<< orphan*/ ,long**,size_t*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tcpp_client_worker (int) ; 
 int tflag ; 
 int /*<<< orphan*/  timespecsub (struct timespec*,struct timespec*,struct timespec*) ; 
 scalar_t__ waitpid (scalar_t__,int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  warn (char*) ; 

void
tcpp_client(void)
{
	struct timespec ts_start, ts_finish;
	long cp_time_start[CPUSTATES], cp_time_finish[CPUSTATES];
	long ticks;
	size_t size;
	pid_t pid;
	int i, failed, status;

	if (bflag < sizeof(struct tcpp_header))
		errx(-1, "Can't use -b less than %zu\n",
		   sizeof(struct tcpp_header));
	payload_len = bflag - sizeof(struct tcpp_header);

	pid_list = malloc(sizeof(*pid_list) * pflag);
	if (pid_list == NULL)
		err(-1, "malloc pid_list");
	bzero(pid_list, sizeof(*pid_list) * pflag);

	/*
	 * Start workers.
	 */
	size = sizeof(cp_time_start);
	if (sysctlbyname(SYSCTLNAME_CPTIME, &cp_time_start, &size, NULL, 0)
	    < 0)
		err(-1, "sysctlbyname: %s", SYSCTLNAME_CPTIME);
	if (clock_gettime(CLOCK_REALTIME, &ts_start) < 0)
		err(-1, "clock_gettime");
	for (i = 0; i < pflag; i++) {
		pid = fork();
		if (pid < 0) {
			warn("fork");
			for (i = 0; i < pflag; i++) {
				if (pid_list[i] != 0)
					(void)kill(pid_list[i], SIGKILL);
			}
			exit(-1);
		}
		if (pid == 0) {
			tcpp_client_worker(i);
			exit(0);
		}
		pid_list[i] = pid;
	}

	/*
	 * GC workers.
	 */
	failed = 0;
	for (i = 0; i < pflag; i++) {
		if (pid_list[i] != 0) {
			while (waitpid(pid_list[i], &status, 0) != pid_list[i]);
			if (WEXITSTATUS(status) != 0)
				failed = 1;
		}
	}
	if (clock_gettime(CLOCK_REALTIME, &ts_finish) < 0)
		err(-1, "clock_gettime");
	size = sizeof(cp_time_finish);
	if (sysctlbyname(SYSCTLNAME_CPTIME, &cp_time_finish, &size, NULL, 0)
	    < 0)
		err(-1, "sysctlbyname: %s", SYSCTLNAME_CPTIME);
	timespecsub(&ts_finish, &ts_start, &ts_finish);

	if (failed)
		errx(-1, "Too many errors");

	if (hflag)
		printf("bytes,seconds,conn/s,Gb/s,user%%,nice%%,sys%%,"
		    "intr%%,idle%%\n");

	/*
	 * Configuration parameters.
	 */
	printf("%jd,", bflag * tflag * pflag);
	printf("%jd.%09jd,", (intmax_t)ts_finish.tv_sec,
	    (intmax_t)(ts_finish.tv_nsec));

	/*
	 * Effective transmit rates.
	 */
	printf("%f,", (double)(pflag * tflag)/
	    (ts_finish.tv_sec + ts_finish.tv_nsec * 1e-9));
	printf("%f,", (double)(bflag * tflag * pflag * 8) /
	    (ts_finish.tv_sec + ts_finish.tv_nsec * 1e-9) * 1e-9);

	/*
	 * CPU time (est).
	 */
	ticks = 0;
	for (i = 0; i < CPUSTATES; i++) {
		cp_time_finish[i] -= cp_time_start[i];
		ticks += cp_time_finish[i];
	}
	printf("%0.02f,", (float)(100 * cp_time_finish[CP_USER]) / ticks);
	printf("%0.02f,", (float)(100 * cp_time_finish[CP_NICE]) / ticks);
	printf("%0.02f,", (float)(100 * cp_time_finish[CP_SYS]) / ticks);
	printf("%0.02f,", (float)(100 * cp_time_finish[CP_INTR]) / ticks);
	printf("%0.02f", (float)(100 * cp_time_finish[CP_IDLE]) / ticks);
	printf("\n");
}