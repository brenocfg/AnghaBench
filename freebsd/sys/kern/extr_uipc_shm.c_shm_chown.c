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
typedef  scalar_t__ uid_t ;
struct ucred {scalar_t__ cr_uid; } ;
struct thread {int dummy; } ;
struct shmfd {scalar_t__ shm_uid; scalar_t__ shm_gid; } ;
struct file {struct shmfd* f_data; } ;
typedef  scalar_t__ gid_t ;

/* Variables and functions */
 int /*<<< orphan*/  PRIV_VFS_CHOWN ; 
 int /*<<< orphan*/  groupmember (scalar_t__,struct ucred*) ; 
 int mac_posixshm_check_setowner (struct ucred*,struct shmfd*,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int priv_check_cred (struct ucred*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  shm_timestamp_lock ; 

__attribute__((used)) static int
shm_chown(struct file *fp, uid_t uid, gid_t gid, struct ucred *active_cred,
    struct thread *td)
{
	struct shmfd *shmfd;
	int error;

	error = 0;
	shmfd = fp->f_data;
	mtx_lock(&shm_timestamp_lock);
#ifdef MAC
	error = mac_posixshm_check_setowner(active_cred, shmfd, uid, gid);
	if (error != 0)
		goto out;
#endif
	if (uid == (uid_t)-1)
		uid = shmfd->shm_uid;
	if (gid == (gid_t)-1)
                 gid = shmfd->shm_gid;
	if (((uid != shmfd->shm_uid && uid != active_cred->cr_uid) ||
	    (gid != shmfd->shm_gid && !groupmember(gid, active_cred))) &&
	    (error = priv_check_cred(active_cred, PRIV_VFS_CHOWN)))
		goto out;
	shmfd->shm_uid = uid;
	shmfd->shm_gid = gid;
out:
	mtx_unlock(&shm_timestamp_lock);
	return (error);
}