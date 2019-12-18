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
struct ucred {scalar_t__ cr_ngroups; int /*<<< orphan*/ * cr_groups; int /*<<< orphan*/  cr_uid; } ;
struct nfscred {int nfsc_ngroups; int /*<<< orphan*/ * nfsc_groups; int /*<<< orphan*/  nfsc_uid; } ;

/* Variables and functions */
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int MIN (scalar_t__,scalar_t__) ; 
 scalar_t__ NFS_MAXGRPS ; 

void
newnfs_copyincred(struct ucred *cr, struct nfscred *nfscr)
{
	int i;

	KASSERT(cr->cr_ngroups >= 0,
	    ("newnfs_copyincred: negative cr_ngroups"));
	nfscr->nfsc_uid = cr->cr_uid;
	nfscr->nfsc_ngroups = MIN(cr->cr_ngroups, NFS_MAXGRPS + 1);
	for (i = 0; i < nfscr->nfsc_ngroups; i++)
		nfscr->nfsc_groups[i] = cr->cr_groups[i];
}