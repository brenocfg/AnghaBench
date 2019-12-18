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
struct thread {int dummy; } ;
struct file {TYPE_1__* f_ops; } ;
typedef  int /*<<< orphan*/  off_t ;
struct TYPE_2__ {int fo_flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  AUDIT_ARG_FD (int) ; 
 int DFLAG_SEEKABLE ; 
 int ESPIPE ; 
 int /*<<< orphan*/  cap_seek_rights ; 
 int /*<<< orphan*/  fdrop (struct file*,struct thread*) ; 
 int fget (struct thread*,int,int /*<<< orphan*/ *,struct file**) ; 
 int fo_seek (struct file*,int /*<<< orphan*/ ,int,struct thread*) ; 

int
kern_lseek(struct thread *td, int fd, off_t offset, int whence)
{
	struct file *fp;
	int error;

	AUDIT_ARG_FD(fd);
	error = fget(td, fd, &cap_seek_rights, &fp);
	if (error != 0)
		return (error);
	error = (fp->f_ops->fo_flags & DFLAG_SEEKABLE) != 0 ?
	    fo_seek(fp, offset, whence, td) : ESPIPE;
	fdrop(fp, td);
	return (error);
}