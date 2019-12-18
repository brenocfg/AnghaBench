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
struct thread {int dummy; } ;
struct cloudabi_sys_fd_seek_args {int whence; int /*<<< orphan*/  offset; int /*<<< orphan*/  fd; } ;

/* Variables and functions */
#define  CLOUDABI_WHENCE_CUR 130 
#define  CLOUDABI_WHENCE_END 129 
#define  CLOUDABI_WHENCE_SET 128 
 int EINVAL ; 
 int SEEK_CUR ; 
 int SEEK_END ; 
 int SEEK_SET ; 
 int kern_lseek (struct thread*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

int
cloudabi_sys_fd_seek(struct thread *td, struct cloudabi_sys_fd_seek_args *uap)
{
	int whence;

	switch (uap->whence) {
	case CLOUDABI_WHENCE_CUR:
		whence = SEEK_CUR;
		break;
	case CLOUDABI_WHENCE_END:
		whence = SEEK_END;
		break;
	case CLOUDABI_WHENCE_SET:
		whence = SEEK_SET;
		break;
	default:
		return (EINVAL);
	}

	return (kern_lseek(td, uap->fd, uap->offset, whence));
}