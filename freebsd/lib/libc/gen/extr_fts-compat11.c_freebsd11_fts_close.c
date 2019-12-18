#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ fts_level; int /*<<< orphan*/  fts_rfd; struct TYPE_5__* fts_path; struct TYPE_5__* fts_array; scalar_t__ fts_child; struct TYPE_5__* fts_parent; struct TYPE_5__* fts_link; struct TYPE_5__* fts_cur; } ;
typedef  TYPE_1__ FTSENT11 ;
typedef  TYPE_1__ FTS11 ;

/* Variables and functions */
 int /*<<< orphan*/  FTS_NOCHDIR ; 
 scalar_t__ FTS_ROOTLEVEL ; 
 int /*<<< orphan*/  ISSET (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _close (int /*<<< orphan*/ ) ; 
 int errno ; 
 scalar_t__ fchdir (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 int /*<<< orphan*/  fts_lfree (scalar_t__) ; 

int
freebsd11_fts_close(FTS11 *sp)
{
	FTSENT11 *freep, *p;
	int saved_errno;

	/*
	 * This still works if we haven't read anything -- the dummy structure
	 * points to the root list, so we step through to the end of the root
	 * list which has a valid parent pointer.
	 */
	if (sp->fts_cur) {
		for (p = sp->fts_cur; p->fts_level >= FTS_ROOTLEVEL;) {
			freep = p;
			p = p->fts_link != NULL ? p->fts_link : p->fts_parent;
			free(freep);
		}
		free(p);
	}

	/* Free up child linked list, sort array, path buffer. */
	if (sp->fts_child)
		fts_lfree(sp->fts_child);
	if (sp->fts_array)
		free(sp->fts_array);
	free(sp->fts_path);

	/* Return to original directory, save errno if necessary. */
	if (!ISSET(FTS_NOCHDIR)) {
		saved_errno = fchdir(sp->fts_rfd) ? errno : 0;
		(void)_close(sp->fts_rfd);

		/* Set errno and return. */
		if (saved_errno != 0) {
			/* Free up the stream pointer. */
			free(sp);
			errno = saved_errno;
			return (-1);
		}
	}

	/* Free up the stream pointer. */
	free(sp);
	return (0);
}