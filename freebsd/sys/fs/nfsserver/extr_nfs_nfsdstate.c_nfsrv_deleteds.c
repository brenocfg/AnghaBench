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
struct nfsdevice {scalar_t__ nfsdev_mdsisset; int /*<<< orphan*/ * nfsdev_nmp; } ;

/* Variables and functions */
 int /*<<< orphan*/  NFSD_DEBUG (int,char*) ; 
 int /*<<< orphan*/  nfsrv_faildscnt ; 

__attribute__((used)) static void
nfsrv_deleteds(struct nfsdevice *fndds)
{

	NFSD_DEBUG(4, "deleteds: deleting a mirror\n");
	fndds->nfsdev_nmp = NULL;
	if (fndds->nfsdev_mdsisset == 0)
		nfsrv_faildscnt--;
}