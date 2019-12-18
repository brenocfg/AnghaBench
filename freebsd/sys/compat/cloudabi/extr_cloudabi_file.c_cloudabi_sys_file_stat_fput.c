#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct timespec {int dummy; } ;
struct thread {int dummy; } ;
struct cloudabi_sys_file_stat_fput_args {int flags; int /*<<< orphan*/  fd; int /*<<< orphan*/  buf; } ;
typedef  int /*<<< orphan*/  fs ;
struct TYPE_4__ {int /*<<< orphan*/  st_size; } ;
typedef  TYPE_1__ cloudabi_filestat_t ;

/* Variables and functions */
 int CLOUDABI_FILESTAT_ATIM ; 
 int CLOUDABI_FILESTAT_ATIM_NOW ; 
 int CLOUDABI_FILESTAT_MTIM ; 
 int CLOUDABI_FILESTAT_MTIM_NOW ; 
 int CLOUDABI_FILESTAT_SIZE ; 
 int EINVAL ; 
 int /*<<< orphan*/  UIO_SYSSPACE ; 
 int /*<<< orphan*/  convert_utimens_arguments (TYPE_1__*,int,struct timespec*) ; 
 int copyin (int /*<<< orphan*/ ,TYPE_1__*,int) ; 
 int kern_ftruncate (struct thread*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int kern_futimens (struct thread*,int /*<<< orphan*/ ,struct timespec*,int /*<<< orphan*/ ) ; 

int
cloudabi_sys_file_stat_fput(struct thread *td,
    struct cloudabi_sys_file_stat_fput_args *uap)
{
	cloudabi_filestat_t fs;
	struct timespec ts[2];
	int error;

	error = copyin(uap->buf, &fs, sizeof(fs));
	if (error != 0)
		return (error);

	/*
	 * Only support truncation and timestamp modification separately
	 * for now, to prevent unnecessary code duplication.
	 */
	if ((uap->flags & CLOUDABI_FILESTAT_SIZE) != 0) {
		/* Call into kern_ftruncate() for file truncation. */
		if ((uap->flags & ~CLOUDABI_FILESTAT_SIZE) != 0)
			return (EINVAL);
		return (kern_ftruncate(td, uap->fd, fs.st_size));
	} else if ((uap->flags & (CLOUDABI_FILESTAT_ATIM |
	    CLOUDABI_FILESTAT_ATIM_NOW | CLOUDABI_FILESTAT_MTIM |
	    CLOUDABI_FILESTAT_MTIM_NOW)) != 0) {
		/* Call into kern_futimens() for timestamp modification. */
		if ((uap->flags & ~(CLOUDABI_FILESTAT_ATIM |
		    CLOUDABI_FILESTAT_ATIM_NOW | CLOUDABI_FILESTAT_MTIM |
		    CLOUDABI_FILESTAT_MTIM_NOW)) != 0)
			return (EINVAL);
		convert_utimens_arguments(&fs, uap->flags, ts);
		return (kern_futimens(td, uap->fd, ts, UIO_SYSSPACE));
	}
	return (EINVAL);
}