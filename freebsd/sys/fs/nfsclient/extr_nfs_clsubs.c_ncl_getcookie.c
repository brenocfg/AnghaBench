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
typedef  int uoff_t ;
struct nfsnode {int /*<<< orphan*/  n_cookies; } ;
struct nfsdmap {int ndm_eocookie; int /*<<< orphan*/ * ndm_cookies; } ;
typedef  scalar_t__ off_t ;
typedef  int /*<<< orphan*/  nfsuint64 ;

/* Variables and functions */
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 struct nfsdmap* LIST_FIRST (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LIST_INSERT_AFTER (struct nfsdmap*,struct nfsdmap*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LIST_INSERT_HEAD (int /*<<< orphan*/ *,struct nfsdmap*,int /*<<< orphan*/ ) ; 
 struct nfsdmap* LIST_NEXT (struct nfsdmap*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  M_NFSDIROFF ; 
 int /*<<< orphan*/  M_WAITOK ; 
 int NFSNUMCOOKIES ; 
 int NFS_DIRBLKSIZ ; 
 struct nfsdmap* malloc (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ndm_list ; 
 int /*<<< orphan*/  nfs_nullcookie ; 

nfsuint64 *
ncl_getcookie(struct nfsnode *np, off_t off, int add)
{
	struct nfsdmap *dp, *dp2;
	int pos;
	nfsuint64 *retval = NULL;
	
	pos = (uoff_t)off / NFS_DIRBLKSIZ;
	if (pos == 0 || off < 0) {
		KASSERT(!add, ("nfs getcookie add at <= 0"));
		return (&nfs_nullcookie);
	}
	pos--;
	dp = LIST_FIRST(&np->n_cookies);
	if (!dp) {
		if (add) {
			dp = malloc(sizeof (struct nfsdmap),
				M_NFSDIROFF, M_WAITOK);
			dp->ndm_eocookie = 0;
			LIST_INSERT_HEAD(&np->n_cookies, dp, ndm_list);
		} else
			goto out;
	}
	while (pos >= NFSNUMCOOKIES) {
		pos -= NFSNUMCOOKIES;
		if (LIST_NEXT(dp, ndm_list)) {
			if (!add && dp->ndm_eocookie < NFSNUMCOOKIES &&
			    pos >= dp->ndm_eocookie)
				goto out;
			dp = LIST_NEXT(dp, ndm_list);
		} else if (add) {
			dp2 = malloc(sizeof (struct nfsdmap),
				M_NFSDIROFF, M_WAITOK);
			dp2->ndm_eocookie = 0;
			LIST_INSERT_AFTER(dp, dp2, ndm_list);
			dp = dp2;
		} else
			goto out;
	}
	if (pos >= dp->ndm_eocookie) {
		if (add)
			dp->ndm_eocookie = pos + 1;
		else
			goto out;
	}
	retval = &dp->ndm_cookies[pos];
out:
	return (retval);
}