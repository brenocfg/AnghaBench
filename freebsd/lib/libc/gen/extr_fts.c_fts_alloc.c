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
struct stat {int dummy; } ;
struct TYPE_7__ {int /*<<< orphan*/  fts_path; } ;
struct TYPE_6__ {char* fts_name; size_t fts_namelen; TYPE_2__* fts_fts; int /*<<< orphan*/ * fts_pointer; scalar_t__ fts_number; int /*<<< orphan*/  fts_instr; scalar_t__ fts_flags; scalar_t__ fts_errno; int /*<<< orphan*/  fts_path; struct stat* fts_statp; } ;
typedef  TYPE_1__ FTSENT ;
typedef  TYPE_2__ FTS ;

/* Variables and functions */
 int /*<<< orphan*/  FTS_NOINSTR ; 
 int /*<<< orphan*/  FTS_NOSTAT ; 
 scalar_t__ ISSET (int /*<<< orphan*/ ) ; 
 TYPE_1__* malloc (size_t) ; 
 int /*<<< orphan*/  memcpy (char*,char*,size_t) ; 

__attribute__((used)) static FTSENT *
fts_alloc(FTS *sp, char *name, size_t namelen)
{
	FTSENT *p;
	size_t len;

	struct ftsent_withstat {
		FTSENT	ent;
		struct	stat statbuf;
	};

	/*
	 * The file name is a variable length array and no stat structure is
	 * necessary if the user has set the nostat bit.  Allocate the FTSENT
	 * structure, the file name and the stat structure in one chunk, but
	 * be careful that the stat structure is reasonably aligned.
	 */
	if (ISSET(FTS_NOSTAT))
		len = sizeof(FTSENT) + namelen + 1;
	else
		len = sizeof(struct ftsent_withstat) + namelen + 1;

	if ((p = malloc(len)) == NULL)
		return (NULL);

	if (ISSET(FTS_NOSTAT)) {
		p->fts_name = (char *)(p + 1);
		p->fts_statp = NULL;
	} else {
		p->fts_name = (char *)((struct ftsent_withstat *)p + 1);
		p->fts_statp = &((struct ftsent_withstat *)p)->statbuf;
	}

	/* Copy the name and guarantee NUL termination. */
	memcpy(p->fts_name, name, namelen);
	p->fts_name[namelen] = '\0';
	p->fts_namelen = namelen;
	p->fts_path = sp->fts_path;
	p->fts_errno = 0;
	p->fts_flags = 0;
	p->fts_instr = FTS_NOINSTR;
	p->fts_number = 0;
	p->fts_pointer = NULL;
	p->fts_fts = sp;
	return (p);
}