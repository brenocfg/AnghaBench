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
struct semstat {int mode; int value; } ;
struct procstat {int dummy; } ;
struct filestat {char* fs_path; int /*<<< orphan*/  fs_fflags; } ;
typedef  int /*<<< orphan*/  mode ;

/* Variables and functions */
 int _POSIX2_LINE_MAX ; 
 scalar_t__ nflg ; 
 int /*<<< orphan*/  print_access_flags (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int procstat_get_sem_info (struct procstat*,struct filestat*,struct semstat*,char*) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int) ; 
 int /*<<< orphan*/  strmode (int,char*) ; 

__attribute__((used)) static void
print_sem_info(struct procstat *procstat, struct filestat *fst)
{
	struct semstat sem;
	char errbuf[_POSIX2_LINE_MAX];
	char mode[15];
	int error;

	error = procstat_get_sem_info(procstat, fst, &sem, errbuf);
	if (error != 0) {
		printf("* error");
		return;
	}
	if (nflg) {
		printf("             ");
		(void)snprintf(mode, sizeof(mode), "%o", sem.mode);
	} else {
		printf(" %-15s", fst->fs_path != NULL ? fst->fs_path : "-");
		strmode(sem.mode, mode);
	}
	printf(" %10s %6u", mode, sem.value);
	print_access_flags(fst->fs_fflags);
}