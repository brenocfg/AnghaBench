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
struct thread {struct proc* td_proc; } ;
struct proc {struct filedesc* p_fd; } ;
struct filedesc {int fd_freefile; int fd_nfiles; TYPE_1__* fd_ofiles; } ;
struct TYPE_2__ {int /*<<< orphan*/ * fde_file; } ;

/* Variables and functions */
 int EMFILE ; 
 int /*<<< orphan*/  FILEDESC_XLOCK_ASSERT (struct filedesc*) ; 
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 scalar_t__ RACCT_ENABLED () ; 
 int /*<<< orphan*/  RACCT_NOFILE ; 
 int fd_first_free (struct filedesc*,int,int) ; 
 int /*<<< orphan*/  fdgrowtable_exp (struct filedesc*,int) ; 
 int /*<<< orphan*/  fdisused (struct filedesc*,int) ; 
 int /*<<< orphan*/  fdused (struct filedesc*,int) ; 
 int getmaxfd (struct thread*) ; 
 int min (int,int) ; 
 int racct_set_unlocked (struct proc*,int /*<<< orphan*/ ,int) ; 

int
fdalloc(struct thread *td, int minfd, int *result)
{
	struct proc *p = td->td_proc;
	struct filedesc *fdp = p->p_fd;
	int fd, maxfd, allocfd;
#ifdef RACCT
	int error;
#endif

	FILEDESC_XLOCK_ASSERT(fdp);

	if (fdp->fd_freefile > minfd)
		minfd = fdp->fd_freefile;

	maxfd = getmaxfd(td);

	/*
	 * Search the bitmap for a free descriptor starting at minfd.
	 * If none is found, grow the file table.
	 */
	fd = fd_first_free(fdp, minfd, fdp->fd_nfiles);
	if (fd >= maxfd)
		return (EMFILE);
	if (fd >= fdp->fd_nfiles) {
		allocfd = min(fd * 2, maxfd);
#ifdef RACCT
		if (RACCT_ENABLED()) {
			error = racct_set_unlocked(p, RACCT_NOFILE, allocfd);
			if (error != 0)
				return (EMFILE);
		}
#endif
		/*
		 * fd is already equal to first free descriptor >= minfd, so
		 * we only need to grow the table and we are done.
		 */
		fdgrowtable_exp(fdp, allocfd);
	}

	/*
	 * Perform some sanity checks, then mark the file descriptor as
	 * used and return it to the caller.
	 */
	KASSERT(fd >= 0 && fd < min(maxfd, fdp->fd_nfiles),
	    ("invalid descriptor %d", fd));
	KASSERT(!fdisused(fdp, fd),
	    ("fd_first_free() returned non-free descriptor"));
	KASSERT(fdp->fd_ofiles[fd].fde_file == NULL,
	    ("file descriptor isn't free"));
	fdused(fdp, fd);
	*result = fd;
	return (0);
}