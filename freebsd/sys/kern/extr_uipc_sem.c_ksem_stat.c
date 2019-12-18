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
struct stat {int st_mode; int /*<<< orphan*/  st_gid; int /*<<< orphan*/  st_uid; int /*<<< orphan*/  st_birthtim; int /*<<< orphan*/  st_mtim; int /*<<< orphan*/  st_ctim; int /*<<< orphan*/  st_atim; } ;
struct ksem {int ks_mode; int /*<<< orphan*/  ks_gid; int /*<<< orphan*/  ks_uid; int /*<<< orphan*/  ks_birthtime; int /*<<< orphan*/  ks_mtime; int /*<<< orphan*/  ks_ctime; int /*<<< orphan*/  ks_atime; } ;
struct file {int /*<<< orphan*/  f_cred; struct ksem* f_data; } ;

/* Variables and functions */
 int S_IFREG ; 
 int /*<<< orphan*/  bzero (struct stat*,int) ; 
 int mac_posixsem_check_stat (struct ucred*,int /*<<< orphan*/ ,struct ksem*) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sem_lock ; 

__attribute__((used)) static int
ksem_stat(struct file *fp, struct stat *sb, struct ucred *active_cred,
    struct thread *td)
{
	struct ksem *ks;
#ifdef MAC
	int error;
#endif

	ks = fp->f_data;

#ifdef MAC
	error = mac_posixsem_check_stat(active_cred, fp->f_cred, ks);
	if (error)
		return (error);
#endif
	
	/*
	 * Attempt to return sanish values for fstat() on a semaphore
	 * file descriptor.
	 */
	bzero(sb, sizeof(*sb));

	mtx_lock(&sem_lock);
	sb->st_atim = ks->ks_atime;
	sb->st_ctim = ks->ks_ctime;
	sb->st_mtim = ks->ks_mtime;
	sb->st_birthtim = ks->ks_birthtime;
	sb->st_uid = ks->ks_uid;
	sb->st_gid = ks->ks_gid;
	sb->st_mode = S_IFREG | ks->ks_mode;		/* XXX */
	mtx_unlock(&sem_lock);

	return (0);
}