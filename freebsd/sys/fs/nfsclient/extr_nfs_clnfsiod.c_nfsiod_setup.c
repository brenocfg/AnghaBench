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
 int /*<<< orphan*/  NFSLOCKIOD () ; 
 int /*<<< orphan*/  NFSUNLOCKIOD () ; 
 scalar_t__ NFS_MAXASYNCDAEMON ; 
 int /*<<< orphan*/  TUNABLE_INT_FETCH (char*,scalar_t__*) ; 
 scalar_t__ ncl_numasync ; 
 scalar_t__ nfs_iodmin ; 
 int nfs_nfsiodnew_sync () ; 
 int /*<<< orphan*/  nfscl_init () ; 
 int /*<<< orphan*/  panic (char*) ; 

__attribute__((used)) static void
nfsiod_setup(void *dummy)
{
	int error;

	TUNABLE_INT_FETCH("vfs.nfs.iodmin", &nfs_iodmin);
	nfscl_init();
	NFSLOCKIOD();
	/* Silently limit the start number of nfsiod's */
	if (nfs_iodmin > NFS_MAXASYNCDAEMON)
		nfs_iodmin = NFS_MAXASYNCDAEMON;

	while (ncl_numasync < nfs_iodmin) {
		error = nfs_nfsiodnew_sync();
		if (error == -1)
			panic("nfsiod_setup: nfs_nfsiodnew failed");
	}
	NFSUNLOCKIOD();
}