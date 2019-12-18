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
struct nameidata {int dummy; } ;
typedef  int /*<<< orphan*/  NFSPROC_T ;

/* Variables and functions */
 int FOLLOW ; 
 int LOCKLEAF ; 
 int /*<<< orphan*/  LOOKUP ; 
 int /*<<< orphan*/  NDFREE (struct nameidata*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NDF_ONLY_PNBUF ; 
 int /*<<< orphan*/  NDINIT (struct nameidata*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  UIO_USERSPACE ; 
 int namei (struct nameidata*) ; 

int
nfsrv_lookupfilename(struct nameidata *ndp, char *fname, NFSPROC_T *p)
{
	int error;

	NDINIT(ndp, LOOKUP, FOLLOW | LOCKLEAF, UIO_USERSPACE, fname,
	    p);
	error = namei(ndp);
	if (!error) {
		NDFREE(ndp, NDF_ONLY_PNBUF);
	}
	return (error);
}