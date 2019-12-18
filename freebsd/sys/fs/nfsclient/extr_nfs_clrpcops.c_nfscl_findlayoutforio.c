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
typedef  scalar_t__ uint64_t ;
typedef  scalar_t__ uint32_t ;
struct nfscllayout {int /*<<< orphan*/  nfsly_flayrw; int /*<<< orphan*/  nfsly_flayread; } ;
struct nfsclflayout {scalar_t__ nfsfl_off; scalar_t__ nfsfl_end; } ;

/* Variables and functions */
 int EIO ; 
 struct nfsclflayout* LIST_FIRST (int /*<<< orphan*/ *) ; 
 struct nfsclflayout* LIST_NEXT (struct nfsclflayout*,int /*<<< orphan*/ ) ; 
 scalar_t__ NFSV4OPEN_ACCESSREAD ; 
 scalar_t__ NFSV4OPEN_ACCESSWRITE ; 
 int /*<<< orphan*/  nfsfl_list ; 

int
nfscl_findlayoutforio(struct nfscllayout *lyp, uint64_t off, uint32_t rwaccess,
    struct nfsclflayout **retflpp)
{
	struct nfsclflayout *flp, *nflp, *rflp;
	uint32_t rw;

	rflp = NULL;
	rw = rwaccess;
	/* For reading, do the Read list first and then the Write list. */
	do {
		if (rw == NFSV4OPEN_ACCESSREAD)
			flp = LIST_FIRST(&lyp->nfsly_flayread);
		else
			flp = LIST_FIRST(&lyp->nfsly_flayrw);
		while (flp != NULL) {
			nflp = LIST_NEXT(flp, nfsfl_list);
			if (flp->nfsfl_off > off)
				break;
			if (flp->nfsfl_end > off &&
			    (rflp == NULL || rflp->nfsfl_end < flp->nfsfl_end))
				rflp = flp;
			flp = nflp;
		}
		if (rw == NFSV4OPEN_ACCESSREAD)
			rw = NFSV4OPEN_ACCESSWRITE;
		else
			rw = 0;
	} while (rw != 0);
	if (rflp != NULL) {
		/* This one covers the most bytes starting at off. */
		*retflpp = rflp;
		return (0);
	}
	return (EIO);
}