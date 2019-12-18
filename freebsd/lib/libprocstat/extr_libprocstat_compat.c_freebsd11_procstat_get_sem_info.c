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
struct semstat {int /*<<< orphan*/  mode; int /*<<< orphan*/  value; } ;
struct procstat {int dummy; } ;
struct freebsd11_semstat {int /*<<< orphan*/  mode; int /*<<< orphan*/  value; } ;
struct filestat {int dummy; } ;

/* Variables and functions */
 int procstat_get_sem_info (struct procstat*,struct filestat*,struct semstat*,char*) ; 

int
freebsd11_procstat_get_sem_info(struct procstat *procstat,
    struct filestat *fst, struct freebsd11_semstat *sem_compat, char *errbuf)
{
	struct semstat sem;
	int r;

	r = procstat_get_sem_info(procstat, fst, &sem, errbuf);
	if (r != 0)
		return (r);
	sem_compat->value = sem.value;
	sem_compat->mode = sem.mode;
	return (0);
}