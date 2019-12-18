#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct filedescent {int /*<<< orphan*/  fde_caps; TYPE_2__* fde_file; } ;
struct filedesc {int fd_freefile; int fd_lastfile; int /*<<< orphan*/  fd_cmask; struct filedescent* fd_ofiles; } ;
struct TYPE_4__ {TYPE_1__* f_ops; } ;
struct TYPE_3__ {int fo_flags; } ;

/* Variables and functions */
 int DFLAG_PASSABLE ; 
 int /*<<< orphan*/  FILEDESC_SUNLOCK (struct filedesc*) ; 
 int /*<<< orphan*/  MPASS (int /*<<< orphan*/ ) ; 
 struct filedesc* fdinit (struct filedesc*,int) ; 
 int /*<<< orphan*/  fdused_init (struct filedesc*,int) ; 
 int /*<<< orphan*/  fhold (TYPE_2__*) ; 
 int /*<<< orphan*/  filecaps_copy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

struct filedesc *
fdcopy(struct filedesc *fdp)
{
	struct filedesc *newfdp;
	struct filedescent *nfde, *ofde;
	int i;

	MPASS(fdp != NULL);

	newfdp = fdinit(fdp, true);
	/* copy all passable descriptors (i.e. not kqueue) */
	newfdp->fd_freefile = -1;
	for (i = 0; i <= fdp->fd_lastfile; ++i) {
		ofde = &fdp->fd_ofiles[i];
		if (ofde->fde_file == NULL ||
		    (ofde->fde_file->f_ops->fo_flags & DFLAG_PASSABLE) == 0 ||
		    !fhold(ofde->fde_file)) {
			if (newfdp->fd_freefile == -1)
				newfdp->fd_freefile = i;
			continue;
		}
		nfde = &newfdp->fd_ofiles[i];
		*nfde = *ofde;
		filecaps_copy(&ofde->fde_caps, &nfde->fde_caps, true);
		fdused_init(newfdp, i);
		newfdp->fd_lastfile = i;
	}
	if (newfdp->fd_freefile == -1)
		newfdp->fd_freefile = i;
	newfdp->fd_cmask = fdp->fd_cmask;
	FILEDESC_SUNLOCK(fdp);
	return (newfdp);
}