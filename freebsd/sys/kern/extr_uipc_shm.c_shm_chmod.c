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
struct ucred {int dummy; } ;
struct thread {int dummy; } ;
struct shmfd {int shm_mode; int /*<<< orphan*/  shm_gid; int /*<<< orphan*/  shm_uid; } ;
struct file {struct shmfd* f_data; } ;
typedef  int mode_t ;

/* Variables and functions */
 int ACCESSPERMS ; 
 int /*<<< orphan*/  VADMIN ; 
 int /*<<< orphan*/  VREG ; 
 int mac_posixshm_check_setmode (struct ucred*,struct shmfd*,int) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  shm_timestamp_lock ; 
 int vaccess (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct ucred*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
shm_chmod(struct file *fp, mode_t mode, struct ucred *active_cred,
    struct thread *td)
{
	struct shmfd *shmfd;
	int error;

	error = 0;
	shmfd = fp->f_data;
	mtx_lock(&shm_timestamp_lock);
	/*
	 * SUSv4 says that x bits of permission need not be affected.
	 * Be consistent with our shm_open there.
	 */
#ifdef MAC
	error = mac_posixshm_check_setmode(active_cred, shmfd, mode);
	if (error != 0)
		goto out;
#endif
	error = vaccess(VREG, shmfd->shm_mode, shmfd->shm_uid,
	    shmfd->shm_gid, VADMIN, active_cred, NULL);
	if (error != 0)
		goto out;
	shmfd->shm_mode = mode & ACCESSPERMS;
out:
	mtx_unlock(&shm_timestamp_lock);
	return (error);
}