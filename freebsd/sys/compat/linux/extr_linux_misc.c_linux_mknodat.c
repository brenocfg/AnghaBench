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
struct thread {int /*<<< orphan*/ * td_retval; } ;
struct linux_mknodat_args {int dfd; int mode; int /*<<< orphan*/  dev; int /*<<< orphan*/  filename; } ;

/* Variables and functions */
 int AT_FDCWD ; 
 int EINVAL ; 
 int EPERM ; 
 int /*<<< orphan*/  LCONVPATHCREAT_AT (struct thread*,int /*<<< orphan*/ ,char**,int) ; 
 int /*<<< orphan*/  LFREEPATH (char*) ; 
 int LINUX_AT_FDCWD ; 
 int O_CREAT ; 
 int O_TRUNC ; 
 int O_WRONLY ; 
#define  S_IFBLK 133 
#define  S_IFCHR 132 
#define  S_IFDIR 131 
#define  S_IFIFO 130 
 int S_IFMT ; 
#define  S_IFREG 129 
#define  S_IFSOCK 128 
 int /*<<< orphan*/  UIO_SYSSPACE ; 
 int /*<<< orphan*/  kern_close (struct thread*,int /*<<< orphan*/ ) ; 
 int kern_mkfifoat (struct thread*,int,char*,int /*<<< orphan*/ ,int) ; 
 int kern_mknodat (struct thread*,int,char*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int kern_openat (struct thread*,int,char*,int /*<<< orphan*/ ,int,int) ; 

int
linux_mknodat(struct thread *td, struct linux_mknodat_args *args)
{
	char *path;
	int error, dfd;

	dfd = (args->dfd == LINUX_AT_FDCWD) ? AT_FDCWD : args->dfd;
	LCONVPATHCREAT_AT(td, args->filename, &path, dfd);

	switch (args->mode & S_IFMT) {
	case S_IFIFO:
	case S_IFSOCK:
		error = kern_mkfifoat(td, dfd, path, UIO_SYSSPACE, args->mode);
		break;

	case S_IFCHR:
	case S_IFBLK:
		error = kern_mknodat(td, dfd, path, UIO_SYSSPACE, args->mode,
		    args->dev);
		break;

	case S_IFDIR:
		error = EPERM;
		break;

	case 0:
		args->mode |= S_IFREG;
		/* FALLTHROUGH */
	case S_IFREG:
		error = kern_openat(td, dfd, path, UIO_SYSSPACE,
		    O_WRONLY | O_CREAT | O_TRUNC, args->mode);
		if (error == 0)
			kern_close(td, td->td_retval[0]);
		break;

	default:
		error = EINVAL;
		break;
	}
	LFREEPATH(path);
	return (error);
}