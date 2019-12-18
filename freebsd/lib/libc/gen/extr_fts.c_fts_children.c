#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {TYPE_1__* fts_child; TYPE_1__* fts_cur; } ;
struct TYPE_7__ {scalar_t__ fts_info; scalar_t__ fts_level; char* fts_accpath; struct TYPE_7__* fts_link; } ;
typedef  TYPE_1__ FTSENT ;
typedef  TYPE_2__ FTS ;

/* Variables and functions */
 int BCHILD ; 
 int BNAMES ; 
 int EINVAL ; 
 scalar_t__ FTS_D ; 
 scalar_t__ FTS_INIT ; 
 int FTS_NAMEONLY ; 
 int /*<<< orphan*/  FTS_NOCHDIR ; 
 scalar_t__ FTS_ROOTLEVEL ; 
 int /*<<< orphan*/  FTS_STOP ; 
 scalar_t__ ISSET (int /*<<< orphan*/ ) ; 
 int O_CLOEXEC ; 
 int O_RDONLY ; 
 int /*<<< orphan*/  SET (int) ; 
 int /*<<< orphan*/  _close (int) ; 
 int _open (char*,int,int /*<<< orphan*/ ) ; 
 int errno ; 
 int fchdir (int) ; 
 void* fts_build (TYPE_2__*,int) ; 
 int /*<<< orphan*/  fts_lfree (TYPE_1__*) ; 

FTSENT *
fts_children(FTS *sp, int instr)
{
	FTSENT *p;
	int fd, rc, serrno;

	if (instr != 0 && instr != FTS_NAMEONLY) {
		errno = EINVAL;
		return (NULL);
	}

	/* Set current node pointer. */
	p = sp->fts_cur;

	/*
	 * Errno set to 0 so user can distinguish empty directory from
	 * an error.
	 */
	errno = 0;

	/* Fatal errors stop here. */
	if (ISSET(FTS_STOP))
		return (NULL);

	/* Return logical hierarchy of user's arguments. */
	if (p->fts_info == FTS_INIT)
		return (p->fts_link);

	/*
	 * If not a directory being visited in pre-order, stop here.  Could
	 * allow FTS_DNR, assuming the user has fixed the problem, but the
	 * same effect is available with FTS_AGAIN.
	 */
	if (p->fts_info != FTS_D /* && p->fts_info != FTS_DNR */)
		return (NULL);

	/* Free up any previous child list. */
	if (sp->fts_child != NULL)
		fts_lfree(sp->fts_child);

	if (instr == FTS_NAMEONLY) {
		SET(FTS_NAMEONLY);
		instr = BNAMES;
	} else
		instr = BCHILD;

	/*
	 * If using chdir on a relative path and called BEFORE fts_read does
	 * its chdir to the root of a traversal, we can lose -- we need to
	 * chdir into the subdirectory, and we don't know where the current
	 * directory is, so we can't get back so that the upcoming chdir by
	 * fts_read will work.
	 */
	if (p->fts_level != FTS_ROOTLEVEL || p->fts_accpath[0] == '/' ||
	    ISSET(FTS_NOCHDIR))
		return (sp->fts_child = fts_build(sp, instr));

	if ((fd = _open(".", O_RDONLY | O_CLOEXEC, 0)) < 0)
		return (NULL);
	sp->fts_child = fts_build(sp, instr);
	serrno = (sp->fts_child == NULL) ? errno : 0;
	rc = fchdir(fd);
	if (rc < 0 && serrno == 0)
		serrno = errno;
	(void)_close(fd);
	errno = serrno;
	if (rc < 0)
		return (NULL);
	return (sp->fts_child);
}