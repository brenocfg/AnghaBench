#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_2__ ;
typedef  struct TYPE_17__   TYPE_1__ ;

/* Type definitions */
struct TYPE_18__ {scalar_t__ fts_dev; char* fts_path; TYPE_1__* fts_cur; void* fts_rfd; TYPE_1__* fts_child; } ;
struct TYPE_17__ {int fts_instr; scalar_t__ fts_info; int fts_errno; int fts_flags; scalar_t__ fts_dev; char* fts_accpath; scalar_t__ fts_level; size_t fts_pathlen; struct TYPE_17__* fts_parent; void* fts_symfd; scalar_t__ fts_namelen; int /*<<< orphan*/  fts_name; struct TYPE_17__* fts_link; } ;
typedef  TYPE_1__ FTSENT ;
typedef  TYPE_2__ FTS ;

/* Variables and functions */
 int /*<<< orphan*/  BREAD ; 
 int /*<<< orphan*/  CLR (int /*<<< orphan*/ ) ; 
 scalar_t__ FCHDIR (TYPE_2__*,void*) ; 
 int FTS_AGAIN ; 
 scalar_t__ FTS_D ; 
 int FTS_DONTCHDIR ; 
 void* FTS_DP ; 
 void* FTS_ERR ; 
 int FTS_FOLLOW ; 
 int /*<<< orphan*/  FTS_NAMEONLY ; 
 int /*<<< orphan*/  FTS_NOCHDIR ; 
 void* FTS_NOINSTR ; 
 scalar_t__ FTS_ROOTLEVEL ; 
 scalar_t__ FTS_ROOTPARENTLEVEL ; 
 int FTS_SKIP ; 
 scalar_t__ FTS_SL ; 
 scalar_t__ FTS_SLNONE ; 
 int /*<<< orphan*/  FTS_STOP ; 
 int FTS_SYMFOLLOW ; 
 int /*<<< orphan*/  FTS_XDEV ; 
 scalar_t__ ISSET (int /*<<< orphan*/ ) ; 
 int NAPPEND (TYPE_1__*) ; 
 int O_CLOEXEC ; 
 int O_RDONLY ; 
 int /*<<< orphan*/  SET (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _close (void*) ; 
 void* _open (char*,int,int /*<<< orphan*/ ) ; 
 int errno ; 
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 TYPE_1__* fts_build (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fts_lfree (TYPE_1__*) ; 
 int /*<<< orphan*/  fts_load (TYPE_2__*,TYPE_1__*) ; 
 scalar_t__ fts_safe_changedir (TYPE_2__*,TYPE_1__*,int,char*) ; 
 void* fts_stat (TYPE_2__*,TYPE_1__*,int) ; 
 int /*<<< orphan*/  memmove (char*,int /*<<< orphan*/ ,scalar_t__) ; 

FTSENT *
__fts_read_44bsd(FTS *sp)
{
	FTSENT *p, *tmp;
	int instr;
	char *t;
	int saved_errno;

	/* If finished or unrecoverable error, return NULL. */
	if (sp->fts_cur == NULL || ISSET(FTS_STOP))
		return (NULL);

	/* Set current node pointer. */
	p = sp->fts_cur;

	/* Save and zero out user instructions. */
	instr = p->fts_instr;
	p->fts_instr = FTS_NOINSTR;

	/* Any type of file may be re-visited; re-stat and re-turn. */
	if (instr == FTS_AGAIN) {
		p->fts_info = fts_stat(sp, p, 0);
		return (p);
	}

	/*
	 * Following a symlink -- SLNONE test allows application to see
	 * SLNONE and recover.  If indirecting through a symlink, have
	 * keep a pointer to current location.  If unable to get that
	 * pointer, follow fails.
	 */
	if (instr == FTS_FOLLOW &&
	    (p->fts_info == FTS_SL || p->fts_info == FTS_SLNONE)) {
		p->fts_info = fts_stat(sp, p, 1);
		if (p->fts_info == FTS_D && !ISSET(FTS_NOCHDIR)) {
			if ((p->fts_symfd = _open(".", O_RDONLY | O_CLOEXEC,
			    0)) < 0) {
				p->fts_errno = errno;
				p->fts_info = FTS_ERR;
			} else
				p->fts_flags |= FTS_SYMFOLLOW;
		}
		return (p);
	}

	/* Directory in pre-order. */
	if (p->fts_info == FTS_D) {
		/* If skipped or crossed mount point, do post-order visit. */
		if (instr == FTS_SKIP ||
		    (ISSET(FTS_XDEV) && p->fts_dev != sp->fts_dev)) {
			if (p->fts_flags & FTS_SYMFOLLOW)
				(void)_close(p->fts_symfd);
			if (sp->fts_child) {
				fts_lfree(sp->fts_child);
				sp->fts_child = NULL;
			}
			p->fts_info = FTS_DP;
			return (p);
		}

		/* Rebuild if only read the names and now traversing. */
		if (sp->fts_child != NULL && ISSET(FTS_NAMEONLY)) {
			CLR(FTS_NAMEONLY);
			fts_lfree(sp->fts_child);
			sp->fts_child = NULL;
		}

		/*
		 * Cd to the subdirectory.
		 *
		 * If have already read and now fail to chdir, whack the list
		 * to make the names come out right, and set the parent errno
		 * so the application will eventually get an error condition.
		 * Set the FTS_DONTCHDIR flag so that when we logically change
		 * directories back to the parent we don't do a chdir.
		 *
		 * If haven't read do so.  If the read fails, fts_build sets
		 * FTS_STOP or the fts_info field of the node.
		 */
		if (sp->fts_child != NULL) {
			if (fts_safe_changedir(sp, p, -1, p->fts_accpath)) {
				p->fts_errno = errno;
				p->fts_flags |= FTS_DONTCHDIR;
				for (p = sp->fts_child; p != NULL;
				    p = p->fts_link)
					p->fts_accpath =
					    p->fts_parent->fts_accpath;
			}
		} else if ((sp->fts_child = fts_build(sp, BREAD)) == NULL) {
			if (ISSET(FTS_STOP))
				return (NULL);
			return (p);
		}
		p = sp->fts_child;
		sp->fts_child = NULL;
		goto name;
	}

	/* Move to the next node on this level. */
next:	tmp = p;
	if ((p = p->fts_link) != NULL) {
		free(tmp);

		/*
		 * If reached the top, return to the original directory (or
		 * the root of the tree), and load the paths for the next root.
		 */
		if (p->fts_level == FTS_ROOTLEVEL) {
			if (FCHDIR(sp, sp->fts_rfd)) {
				SET(FTS_STOP);
				return (NULL);
			}
			fts_load(sp, p);
			return (sp->fts_cur = p);
		}

		/*
		 * User may have called fts_set on the node.  If skipped,
		 * ignore.  If followed, get a file descriptor so we can
		 * get back if necessary.
		 */
		if (p->fts_instr == FTS_SKIP)
			goto next;
		if (p->fts_instr == FTS_FOLLOW) {
			p->fts_info = fts_stat(sp, p, 1);
			if (p->fts_info == FTS_D && !ISSET(FTS_NOCHDIR)) {
				if ((p->fts_symfd =
				    _open(".", O_RDONLY | O_CLOEXEC, 0)) < 0) {
					p->fts_errno = errno;
					p->fts_info = FTS_ERR;
				} else
					p->fts_flags |= FTS_SYMFOLLOW;
			}
			p->fts_instr = FTS_NOINSTR;
		}

name:		t = sp->fts_path + NAPPEND(p->fts_parent);
		*t++ = '/';
		memmove(t, p->fts_name, p->fts_namelen + 1);
		return (sp->fts_cur = p);
	}

	/* Move up to the parent node. */
	p = tmp->fts_parent;
	free(tmp);

	if (p->fts_level == FTS_ROOTPARENTLEVEL) {
		/*
		 * Done; free everything up and set errno to 0 so the user
		 * can distinguish between error and EOF.
		 */
		free(p);
		errno = 0;
		return (sp->fts_cur = NULL);
	}

	/* NUL terminate the pathname. */
	sp->fts_path[p->fts_pathlen] = '\0';

	/*
	 * Return to the parent directory.  If at a root node or came through
	 * a symlink, go back through the file descriptor.  Otherwise, cd up
	 * one directory.
	 */
	if (p->fts_level == FTS_ROOTLEVEL) {
		if (FCHDIR(sp, sp->fts_rfd)) {
			SET(FTS_STOP);
			return (NULL);
		}
	} else if (p->fts_flags & FTS_SYMFOLLOW) {
		if (FCHDIR(sp, p->fts_symfd)) {
			saved_errno = errno;
			(void)_close(p->fts_symfd);
			errno = saved_errno;
			SET(FTS_STOP);
			return (NULL);
		}
		(void)_close(p->fts_symfd);
	} else if (!(p->fts_flags & FTS_DONTCHDIR) &&
	    fts_safe_changedir(sp, p->fts_parent, -1, "..")) {
		SET(FTS_STOP);
		return (NULL);
	}
	p->fts_info = p->fts_errno ? FTS_ERR : FTS_DP;
	return (sp->fts_cur = p);
}