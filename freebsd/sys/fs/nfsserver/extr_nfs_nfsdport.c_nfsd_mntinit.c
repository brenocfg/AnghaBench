#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int mnt_flag; scalar_t__ mnt_activevnodelistsize; scalar_t__ mnt_nvnodelistsize; int /*<<< orphan*/ * mnt_optnew; int /*<<< orphan*/ * mnt_opt; int /*<<< orphan*/ * mnt_export; int /*<<< orphan*/  mnt_activevnodelist; int /*<<< orphan*/  mnt_nvnodelist; } ;

/* Variables and functions */
 int MNT_EXPORTED ; 
 int MNT_RDONLY ; 
 int /*<<< orphan*/  TAILQ_INIT (int /*<<< orphan*/ *) ; 
 TYPE_1__ nfsv4root_mnt ; 
 int /*<<< orphan*/  nfsv4root_newopt ; 
 int /*<<< orphan*/  nfsv4root_opt ; 

void
nfsd_mntinit(void)
{
	static int inited = 0;

	if (inited)
		return;
	inited = 1;
	nfsv4root_mnt.mnt_flag = (MNT_RDONLY | MNT_EXPORTED);
	TAILQ_INIT(&nfsv4root_mnt.mnt_nvnodelist);
	TAILQ_INIT(&nfsv4root_mnt.mnt_activevnodelist);
	nfsv4root_mnt.mnt_export = NULL;
	TAILQ_INIT(&nfsv4root_opt);
	TAILQ_INIT(&nfsv4root_newopt);
	nfsv4root_mnt.mnt_opt = &nfsv4root_opt;
	nfsv4root_mnt.mnt_optnew = &nfsv4root_newopt;
	nfsv4root_mnt.mnt_nvnodelistsize = 0;
	nfsv4root_mnt.mnt_activevnodelistsize = 0;
}