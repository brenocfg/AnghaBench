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

/* Variables and functions */
 int /*<<< orphan*/  NFSASSERTIOD () ; 
 int /*<<< orphan*/  NFSIOD_AVAILABLE ; 
 int /*<<< orphan*/  NFSLOCKIOD () ; 
 int /*<<< orphan*/  NFSUNLOCKIOD () ; 
 int /*<<< orphan*/  RFHIGHPID ; 
 int kproc_create (int /*<<< orphan*/ ,int*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int) ; 
 int ncl_iodmax ; 
 int /*<<< orphan*/ * ncl_iodwant ; 
 int /*<<< orphan*/  ncl_numasync ; 
 int* nfs_asyncdaemon ; 
 int /*<<< orphan*/  nfssvc_iod ; 

__attribute__((used)) static int
nfs_nfsiodnew_sync(void)
{
	int error, i;

	NFSASSERTIOD();
	for (i = 0; i < ncl_iodmax; i++) {
		if (nfs_asyncdaemon[i] == 0) {
			nfs_asyncdaemon[i] = 1;
			break;
		}
	}
	if (i == ncl_iodmax)
		return (0);
	NFSUNLOCKIOD();
	error = kproc_create(nfssvc_iod, nfs_asyncdaemon + i, NULL,
	    RFHIGHPID, 0, "newnfs %d", i);
	NFSLOCKIOD();
	if (error == 0) {
		ncl_numasync++;
		ncl_iodwant[i] = NFSIOD_AVAILABLE;
	} else
		nfs_asyncdaemon[i] = 0;
	return (error);
}