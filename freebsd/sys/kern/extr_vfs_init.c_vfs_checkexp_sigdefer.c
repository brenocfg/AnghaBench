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
struct ucred {int dummy; } ;
struct sockaddr {int dummy; } ;
struct mount {TYPE_2__* mnt_vfc; } ;
struct TYPE_4__ {TYPE_1__* vfc_vfsops_sd; } ;
struct TYPE_3__ {int (* vfs_checkexp ) (struct mount*,struct sockaddr*,int*,struct ucred**,int*,int**) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  SIGDEFERSTOP_SILENT ; 
 int /*<<< orphan*/  sigallowstop (int) ; 
 int sigdeferstop (int /*<<< orphan*/ ) ; 
 int stub1 (struct mount*,struct sockaddr*,int*,struct ucred**,int*,int**) ; 

__attribute__((used)) static int
vfs_checkexp_sigdefer(struct mount *mp, struct sockaddr *nam, int *exflg,
    struct ucred **credp, int *numsecflavors, int **secflavors)
{
	int prev_stops, rc;

	prev_stops = sigdeferstop(SIGDEFERSTOP_SILENT);
	rc = (*mp->mnt_vfc->vfc_vfsops_sd->vfs_checkexp)(mp, nam, exflg, credp,
	    numsecflavors, secflavors);
	sigallowstop(prev_stops);
	return (rc);
}