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
typedef  scalar_t__ uid_t ;
typedef  int /*<<< orphan*/  u_long ;
struct TYPE_2__ {int uid; int gid; int cuid; int cgid; int mode; } ;
struct shmid_ds {TYPE_1__ shm_perm; int /*<<< orphan*/  shm_ctime; int /*<<< orphan*/  shm_dtime; int /*<<< orphan*/  shm_atime; int /*<<< orphan*/  shm_nattch; int /*<<< orphan*/  shm_cpid; int /*<<< orphan*/  shm_lpid; scalar_t__ shm_segsz; } ;
typedef  int mode_t ;
typedef  scalar_t__ gid_t ;

/* Variables and functions */
 char* ctime (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  errx (int,char*) ; 
 scalar_t__ getegid () ; 
 scalar_t__ geteuid () ; 
 int /*<<< orphan*/  printf (char*,...) ; 

__attribute__((used)) static void
print_shmid_ds(struct shmid_ds *sp, mode_t mode)
{
	uid_t uid = geteuid();
	gid_t gid = getegid();

	printf("PERM: uid %d, gid %d, cuid %d, cgid %d, mode 0%o\n",
	    sp->shm_perm.uid, sp->shm_perm.gid,
	    sp->shm_perm.cuid, sp->shm_perm.cgid,
	    sp->shm_perm.mode & 0777);

	printf("segsz %lu, lpid %d, cpid %d, nattch %u\n",
	    (u_long)sp->shm_segsz, sp->shm_lpid, sp->shm_cpid,
	    sp->shm_nattch);

	printf("atime: %s", ctime(&sp->shm_atime));
	printf("dtime: %s", ctime(&sp->shm_dtime));
	printf("ctime: %s", ctime(&sp->shm_ctime));

	/*
	 * Sanity check a few things.
	 */

	if (sp->shm_perm.uid != uid || sp->shm_perm.cuid != uid)
		errx(1, "uid mismatch");

	if (sp->shm_perm.gid != gid || sp->shm_perm.cgid != gid)
		errx(1, "gid mismatch");

	if ((sp->shm_perm.mode & 0777) != mode)
		errx(1, "mode mismatch");
}