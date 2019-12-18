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
struct thread {int dummy; } ;
struct statfs {int dummy; } ;
struct nameidata {TYPE_1__* ni_vp; } ;
struct mount {int dummy; } ;
typedef  enum uio_seg { ____Placeholder_uio_seg } uio_seg ;
struct TYPE_2__ {struct mount* v_mount; } ;

/* Variables and functions */
 int AUDITVNODE1 ; 
 int FOLLOW ; 
 int LOCKLEAF ; 
 int LOCKSHARED ; 
 int /*<<< orphan*/  LOOKUP ; 
 int /*<<< orphan*/  NDFREE (struct nameidata*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NDF_ONLY_PNBUF ; 
 int /*<<< orphan*/  NDINIT (struct nameidata*,int /*<<< orphan*/ ,int,int,char const*,struct thread*) ; 
 int kern_do_statfs (struct thread*,struct mount*,struct statfs*) ; 
 int namei (struct nameidata*) ; 
 int /*<<< orphan*/  vfs_ref (struct mount*) ; 
 int /*<<< orphan*/  vput (TYPE_1__*) ; 

int
kern_statfs(struct thread *td, const char *path, enum uio_seg pathseg,
    struct statfs *buf)
{
	struct mount *mp;
	struct nameidata nd;
	int error;

	NDINIT(&nd, LOOKUP, FOLLOW | LOCKSHARED | LOCKLEAF | AUDITVNODE1,
	    pathseg, path, td);
	error = namei(&nd);
	if (error != 0)
		return (error);
	mp = nd.ni_vp->v_mount;
	vfs_ref(mp);
	NDFREE(&nd, NDF_ONLY_PNBUF);
	vput(nd.ni_vp);
	return (kern_do_statfs(td, mp, buf));
}