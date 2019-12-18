#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct sockaddr_in {int dummy; } ;
struct ifaliasreq {int dummy; } ;
struct TYPE_6__ {int flags; } ;
struct TYPE_5__ {int /*<<< orphan*/ * my_hostnam; int /*<<< orphan*/  root_time; int /*<<< orphan*/ * root_hostnam; int /*<<< orphan*/  root_saddr; int /*<<< orphan*/ * root_fh; int /*<<< orphan*/  root_args; int /*<<< orphan*/  mygateway; int /*<<< orphan*/  myif; } ;
struct TYPE_4__ {int root_fhsize; int /*<<< orphan*/ * my_hostnam; int /*<<< orphan*/  root_time; int /*<<< orphan*/ * root_hostnam; int /*<<< orphan*/  root_saddr; int /*<<< orphan*/ * root_fh; TYPE_3__ root_args; int /*<<< orphan*/  mygateway; int /*<<< orphan*/  myif; } ;

/* Variables and functions */
 int MAXHOSTNAMELEN ; 
 int MNAMELEN ; 
 int NFSMNT_NFSV3 ; 
 int NFSX_MYFH ; 
 int NFSX_V2FH ; 
 int /*<<< orphan*/  bcopy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  nfs_convert_oargs (TYPE_3__*,int /*<<< orphan*/ *) ; 
 TYPE_2__ nfs_diskless ; 
 int nfs_diskless_valid ; 
 TYPE_1__ nfsv3_diskless ; 

__attribute__((used)) static void
nfs_convert_diskless(void)
{

	bcopy(&nfs_diskless.myif, &nfsv3_diskless.myif,
		sizeof(struct ifaliasreq));
	bcopy(&nfs_diskless.mygateway, &nfsv3_diskless.mygateway,
		sizeof(struct sockaddr_in));
	nfs_convert_oargs(&nfsv3_diskless.root_args,&nfs_diskless.root_args);
	if (nfsv3_diskless.root_args.flags & NFSMNT_NFSV3) {
		nfsv3_diskless.root_fhsize = NFSX_MYFH;
		bcopy(nfs_diskless.root_fh, nfsv3_diskless.root_fh, NFSX_MYFH);
	} else {
		nfsv3_diskless.root_fhsize = NFSX_V2FH;
		bcopy(nfs_diskless.root_fh, nfsv3_diskless.root_fh, NFSX_V2FH);
	}
	bcopy(&nfs_diskless.root_saddr,&nfsv3_diskless.root_saddr,
		sizeof(struct sockaddr_in));
	bcopy(nfs_diskless.root_hostnam, nfsv3_diskless.root_hostnam, MNAMELEN);
	nfsv3_diskless.root_time = nfs_diskless.root_time;
	bcopy(nfs_diskless.my_hostnam, nfsv3_diskless.my_hostnam,
		MAXHOSTNAMELEN);
	nfs_diskless_valid = 3;
}