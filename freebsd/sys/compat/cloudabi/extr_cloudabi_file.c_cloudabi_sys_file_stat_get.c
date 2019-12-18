#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct thread {int dummy; } ;
struct stat {int /*<<< orphan*/  st_mode; } ;
struct TYPE_6__ {int flags; int /*<<< orphan*/  fd; } ;
struct cloudabi_sys_file_stat_get_args {int /*<<< orphan*/  buf; TYPE_1__ fd; int /*<<< orphan*/  path_len; int /*<<< orphan*/  path; } ;
typedef  int /*<<< orphan*/  csb ;
struct TYPE_7__ {void* st_filetype; } ;
typedef  TYPE_2__ cloudabi_filestat_t ;

/* Variables and functions */
 int /*<<< orphan*/  AT_SYMLINK_NOFOLLOW ; 
 void* CLOUDABI_FILETYPE_BLOCK_DEVICE ; 
 void* CLOUDABI_FILETYPE_CHARACTER_DEVICE ; 
 void* CLOUDABI_FILETYPE_DIRECTORY ; 
 void* CLOUDABI_FILETYPE_REGULAR_FILE ; 
 void* CLOUDABI_FILETYPE_SOCKET_STREAM ; 
 void* CLOUDABI_FILETYPE_SYMBOLIC_LINK ; 
 void* CLOUDABI_FILETYPE_UNKNOWN ; 
 int CLOUDABI_LOOKUP_SYMLINK_FOLLOW ; 
 scalar_t__ S_ISBLK (int /*<<< orphan*/ ) ; 
 scalar_t__ S_ISCHR (int /*<<< orphan*/ ) ; 
 scalar_t__ S_ISDIR (int /*<<< orphan*/ ) ; 
 scalar_t__ S_ISFIFO (int /*<<< orphan*/ ) ; 
 scalar_t__ S_ISLNK (int /*<<< orphan*/ ) ; 
 scalar_t__ S_ISREG (int /*<<< orphan*/ ) ; 
 scalar_t__ S_ISSOCK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UIO_SYSSPACE ; 
 int /*<<< orphan*/  cloudabi_freestr (char*) ; 
 int /*<<< orphan*/  convert_stat (struct stat*,TYPE_2__*) ; 
 int copyin_path (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char**) ; 
 int copyout (TYPE_2__*,int /*<<< orphan*/ ,int) ; 
 int kern_statat (struct thread*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,struct stat*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (TYPE_2__*,int /*<<< orphan*/ ,int) ; 

int
cloudabi_sys_file_stat_get(struct thread *td,
    struct cloudabi_sys_file_stat_get_args *uap)
{
	struct stat sb;
	cloudabi_filestat_t csb;
	char *path;
	int error;

	memset(&csb, 0, sizeof(csb));

	error = copyin_path(uap->path, uap->path_len, &path);
	if (error != 0)
		return (error);

	error = kern_statat(td,
	    (uap->fd.flags & CLOUDABI_LOOKUP_SYMLINK_FOLLOW) != 0 ? 0 :
	    AT_SYMLINK_NOFOLLOW, uap->fd.fd, path, UIO_SYSSPACE, &sb, NULL);
	cloudabi_freestr(path);
	if (error != 0)
		return (error);

	/* Convert results and return them. */
	convert_stat(&sb, &csb);
	if (S_ISBLK(sb.st_mode))
		csb.st_filetype = CLOUDABI_FILETYPE_BLOCK_DEVICE;
	else if (S_ISCHR(sb.st_mode))
		csb.st_filetype = CLOUDABI_FILETYPE_CHARACTER_DEVICE;
	else if (S_ISDIR(sb.st_mode))
		csb.st_filetype = CLOUDABI_FILETYPE_DIRECTORY;
	else if (S_ISFIFO(sb.st_mode))
		csb.st_filetype = CLOUDABI_FILETYPE_SOCKET_STREAM;
	else if (S_ISREG(sb.st_mode))
		csb.st_filetype = CLOUDABI_FILETYPE_REGULAR_FILE;
	else if (S_ISSOCK(sb.st_mode)) {
		/* Inaccurate, but the best that we can do. */
		csb.st_filetype = CLOUDABI_FILETYPE_SOCKET_STREAM;
	} else if (S_ISLNK(sb.st_mode))
		csb.st_filetype = CLOUDABI_FILETYPE_SYMBOLIC_LINK;
	else
		csb.st_filetype = CLOUDABI_FILETYPE_UNKNOWN;
	return (copyout(&csb, uap->buf, sizeof(csb)));
}