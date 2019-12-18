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
struct pipe {int dummy; } ;
struct pipepair {struct pipe pp_wpipe; struct pipe pp_rpipe; } ;
struct filecaps {int dummy; } ;
struct file {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DTYPE_PIPE ; 
 int FNONBLOCK ; 
 int FREAD ; 
 int FWRITE ; 
 int O_NONBLOCK ; 
 int falloc_caps (struct thread*,struct file**,int*,int,struct filecaps*) ; 
 int /*<<< orphan*/  fdclose (struct thread*,struct file*,int) ; 
 int /*<<< orphan*/  fdrop (struct file*,struct thread*) ; 
 int /*<<< orphan*/  finit (struct file*,int,int /*<<< orphan*/ ,struct pipe*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pipe_paircreate (struct thread*,struct pipepair**) ; 
 int /*<<< orphan*/  pipeclose (struct pipe*) ; 
 int /*<<< orphan*/  pipeops ; 

int
kern_pipe(struct thread *td, int fildes[2], int flags, struct filecaps *fcaps1,
    struct filecaps *fcaps2)
{
	struct file *rf, *wf;
	struct pipe *rpipe, *wpipe;
	struct pipepair *pp;
	int fd, fflags, error;

	pipe_paircreate(td, &pp);
	rpipe = &pp->pp_rpipe;
	wpipe = &pp->pp_wpipe;
	error = falloc_caps(td, &rf, &fd, flags, fcaps1);
	if (error) {
		pipeclose(rpipe);
		pipeclose(wpipe);
		return (error);
	}
	/* An extra reference on `rf' has been held for us by falloc_caps(). */
	fildes[0] = fd;

	fflags = FREAD | FWRITE;
	if ((flags & O_NONBLOCK) != 0)
		fflags |= FNONBLOCK;

	/*
	 * Warning: once we've gotten past allocation of the fd for the
	 * read-side, we can only drop the read side via fdrop() in order
	 * to avoid races against processes which manage to dup() the read
	 * side while we are blocked trying to allocate the write side.
	 */
	finit(rf, fflags, DTYPE_PIPE, rpipe, &pipeops);
	error = falloc_caps(td, &wf, &fd, flags, fcaps2);
	if (error) {
		fdclose(td, rf, fildes[0]);
		fdrop(rf, td);
		/* rpipe has been closed by fdrop(). */
		pipeclose(wpipe);
		return (error);
	}
	/* An extra reference on `wf' has been held for us by falloc_caps(). */
	finit(wf, fflags, DTYPE_PIPE, wpipe, &pipeops);
	fdrop(wf, td);
	fildes[1] = fd;
	fdrop(rf, td);

	return (0);
}