#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct ucred {int dummy; } ;
struct thread {int dummy; } ;
struct stat {scalar_t__ st_size; int /*<<< orphan*/  st_ino; int /*<<< orphan*/  st_dev; int /*<<< orphan*/  st_gid; int /*<<< orphan*/  st_uid; int /*<<< orphan*/  st_ctim; int /*<<< orphan*/  st_mtim; int /*<<< orphan*/  st_atim; int /*<<< orphan*/  st_blksize; int /*<<< orphan*/  st_blocks; int /*<<< orphan*/  st_mode; } ;
struct TYPE_6__ {scalar_t__ cnt; } ;
struct TYPE_5__ {scalar_t__ cnt; } ;
struct pipe {int pipe_state; int /*<<< orphan*/  pipe_ino; int /*<<< orphan*/  pipe_ctime; int /*<<< orphan*/  pipe_mtime; int /*<<< orphan*/  pipe_atime; TYPE_2__ pipe_buffer; TYPE_1__ pipe_map; int /*<<< orphan*/  pipe_pair; } ;
struct file {TYPE_3__* f_cred; struct pipe* f_data; } ;
struct TYPE_8__ {int (* fo_stat ) (struct file*,struct stat*,struct ucred*,struct thread*) ;} ;
struct TYPE_7__ {int /*<<< orphan*/  cr_gid; int /*<<< orphan*/  cr_uid; } ;

/* Variables and functions */
 int /*<<< orphan*/  PAGE_SIZE ; 
 int /*<<< orphan*/  PIPE_LOCK (struct pipe*) ; 
 int PIPE_NAMED ; 
 int /*<<< orphan*/  PIPE_UNLOCK (struct pipe*) ; 
 int /*<<< orphan*/  S_IFIFO ; 
 int /*<<< orphan*/  bzero (struct stat*,int) ; 
 int /*<<< orphan*/  howmany (scalar_t__,int /*<<< orphan*/ ) ; 
 int mac_pipe_check_stat (struct ucred*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pipedev_ino ; 
 int stub1 (struct file*,struct stat*,struct ucred*,struct thread*) ; 
 TYPE_4__ vnops ; 

__attribute__((used)) static int
pipe_stat(struct file *fp, struct stat *ub, struct ucred *active_cred,
    struct thread *td)
{
	struct pipe *pipe;
#ifdef MAC
	int error;
#endif

	pipe = fp->f_data;
	PIPE_LOCK(pipe);
#ifdef MAC
	error = mac_pipe_check_stat(active_cred, pipe->pipe_pair);
	if (error) {
		PIPE_UNLOCK(pipe);
		return (error);
	}
#endif

	/* For named pipes ask the underlying filesystem. */
	if (pipe->pipe_state & PIPE_NAMED) {
		PIPE_UNLOCK(pipe);
		return (vnops.fo_stat(fp, ub, active_cred, td));
	}

	PIPE_UNLOCK(pipe);

	bzero(ub, sizeof(*ub));
	ub->st_mode = S_IFIFO;
	ub->st_blksize = PAGE_SIZE;
	if (pipe->pipe_map.cnt != 0)
		ub->st_size = pipe->pipe_map.cnt;
	else
		ub->st_size = pipe->pipe_buffer.cnt;
	ub->st_blocks = howmany(ub->st_size, ub->st_blksize);
	ub->st_atim = pipe->pipe_atime;
	ub->st_mtim = pipe->pipe_mtime;
	ub->st_ctim = pipe->pipe_ctime;
	ub->st_uid = fp->f_cred->cr_uid;
	ub->st_gid = fp->f_cred->cr_gid;
	ub->st_dev = pipedev_ino;
	ub->st_ino = pipe->pipe_ino;
	/*
	 * Left as 0: st_nlink, st_rdev, st_flags, st_gen.
	 */
	return (0);
}