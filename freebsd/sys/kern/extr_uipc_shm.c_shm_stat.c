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
struct ucred {int dummy; } ;
struct thread {int dummy; } ;
struct stat {int st_mode; int /*<<< orphan*/  st_nlink; int /*<<< orphan*/  st_ino; int /*<<< orphan*/  st_dev; int /*<<< orphan*/  st_gid; int /*<<< orphan*/  st_uid; int /*<<< orphan*/  st_birthtim; int /*<<< orphan*/  st_mtim; int /*<<< orphan*/  st_ctim; int /*<<< orphan*/  st_atim; int /*<<< orphan*/  st_blksize; int /*<<< orphan*/  st_size; int /*<<< orphan*/  st_blocks; } ;
struct shmfd {int shm_mode; TYPE_1__* shm_object; int /*<<< orphan*/  shm_ino; int /*<<< orphan*/  shm_gid; int /*<<< orphan*/  shm_uid; int /*<<< orphan*/  shm_birthtime; int /*<<< orphan*/  shm_mtime; int /*<<< orphan*/  shm_ctime; int /*<<< orphan*/  shm_atime; int /*<<< orphan*/  shm_size; } ;
struct file {int /*<<< orphan*/  f_cred; struct shmfd* f_data; } ;
struct TYPE_2__ {int /*<<< orphan*/  ref_count; } ;

/* Variables and functions */
 int /*<<< orphan*/  PAGE_SIZE ; 
 int S_IFREG ; 
 int /*<<< orphan*/  bzero (struct stat*,int) ; 
 int /*<<< orphan*/  howmany (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int mac_posixshm_check_stat (struct ucred*,int /*<<< orphan*/ ,struct shmfd*) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  shm_dev_ino ; 
 int /*<<< orphan*/  shm_timestamp_lock ; 

__attribute__((used)) static int
shm_stat(struct file *fp, struct stat *sb, struct ucred *active_cred,
    struct thread *td)
{
	struct shmfd *shmfd;
#ifdef MAC
	int error;
#endif

	shmfd = fp->f_data;

#ifdef MAC
	error = mac_posixshm_check_stat(active_cred, fp->f_cred, shmfd);
	if (error)
		return (error);
#endif
	
	/*
	 * Attempt to return sanish values for fstat() on a memory file
	 * descriptor.
	 */
	bzero(sb, sizeof(*sb));
	sb->st_blksize = PAGE_SIZE;
	sb->st_size = shmfd->shm_size;
	sb->st_blocks = howmany(sb->st_size, sb->st_blksize);
	mtx_lock(&shm_timestamp_lock);
	sb->st_atim = shmfd->shm_atime;
	sb->st_ctim = shmfd->shm_ctime;
	sb->st_mtim = shmfd->shm_mtime;
	sb->st_birthtim = shmfd->shm_birthtime;
	sb->st_mode = S_IFREG | shmfd->shm_mode;		/* XXX */
	sb->st_uid = shmfd->shm_uid;
	sb->st_gid = shmfd->shm_gid;
	mtx_unlock(&shm_timestamp_lock);
	sb->st_dev = shm_dev_ino;
	sb->st_ino = shmfd->shm_ino;
	sb->st_nlink = shmfd->shm_object->ref_count;

	return (0);
}