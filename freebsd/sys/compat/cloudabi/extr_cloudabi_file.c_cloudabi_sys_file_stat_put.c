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
struct timespec {int dummy; } ;
struct thread {int dummy; } ;
struct TYPE_2__ {int flags; int /*<<< orphan*/  fd; } ;
struct cloudabi_sys_file_stat_put_args {int flags; TYPE_1__ fd; int /*<<< orphan*/  path_len; int /*<<< orphan*/  path; int /*<<< orphan*/  buf; } ;
typedef  int /*<<< orphan*/  fs ;
typedef  int /*<<< orphan*/  cloudabi_filestat_t ;

/* Variables and functions */
 int /*<<< orphan*/  AT_SYMLINK_NOFOLLOW ; 
 int CLOUDABI_FILESTAT_ATIM ; 
 int CLOUDABI_FILESTAT_ATIM_NOW ; 
 int CLOUDABI_FILESTAT_MTIM ; 
 int CLOUDABI_FILESTAT_MTIM_NOW ; 
 int CLOUDABI_LOOKUP_SYMLINK_FOLLOW ; 
 int EINVAL ; 
 int /*<<< orphan*/  UIO_SYSSPACE ; 
 int /*<<< orphan*/  cloudabi_freestr (char*) ; 
 int /*<<< orphan*/  convert_utimens_arguments (int /*<<< orphan*/ *,int,struct timespec*) ; 
 int copyin (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int copyin_path (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char**) ; 
 int kern_utimensat (struct thread*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,struct timespec*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int
cloudabi_sys_file_stat_put(struct thread *td,
    struct cloudabi_sys_file_stat_put_args *uap)
{
	cloudabi_filestat_t fs;
	struct timespec ts[2];
	char *path;
	int error;

	/*
	 * Only support timestamp modification for now, as there is no
	 * truncateat().
	 */
	if ((uap->flags & ~(CLOUDABI_FILESTAT_ATIM |
	    CLOUDABI_FILESTAT_ATIM_NOW | CLOUDABI_FILESTAT_MTIM |
	    CLOUDABI_FILESTAT_MTIM_NOW)) != 0)
		return (EINVAL);

	error = copyin(uap->buf, &fs, sizeof(fs));
	if (error != 0)
		return (error);
	error = copyin_path(uap->path, uap->path_len, &path);
	if (error != 0)
		return (error);

	convert_utimens_arguments(&fs, uap->flags, ts);
	error = kern_utimensat(td, uap->fd.fd, path, UIO_SYSSPACE, ts,
	    UIO_SYSSPACE, (uap->fd.flags & CLOUDABI_LOOKUP_SYMLINK_FOLLOW) ?
	    0 : AT_SYMLINK_NOFOLLOW);
	cloudabi_freestr(path);
	return (error);
}