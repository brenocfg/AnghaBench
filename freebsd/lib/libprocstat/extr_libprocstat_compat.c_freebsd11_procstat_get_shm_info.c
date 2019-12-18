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
struct shmstat {int /*<<< orphan*/  mode; int /*<<< orphan*/  size; } ;
struct procstat {int dummy; } ;
struct freebsd11_shmstat {int /*<<< orphan*/  mode; int /*<<< orphan*/  size; } ;
struct filestat {int dummy; } ;

/* Variables and functions */
 int procstat_get_shm_info (struct procstat*,struct filestat*,struct shmstat*,char*) ; 

int
freebsd11_procstat_get_shm_info(struct procstat *procstat,
    struct filestat *fst, struct freebsd11_shmstat *shm_compat, char *errbuf)
{
	struct shmstat shm;
	int r;

	r = procstat_get_shm_info(procstat, fst, &shm, errbuf);
	if (r != 0)
		return (r);
	shm_compat->size = shm.size;
	shm_compat->mode = shm.mode;
	return (0);
}