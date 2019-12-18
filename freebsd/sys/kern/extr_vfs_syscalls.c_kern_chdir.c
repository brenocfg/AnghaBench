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
struct thread {int dummy; } ;
struct nameidata {int /*<<< orphan*/  ni_vp; } ;
typedef  enum uio_seg { ____Placeholder_uio_seg } uio_seg ;

/* Variables and functions */
 int AUDITVNODE1 ; 
 int FOLLOW ; 
 int LOCKLEAF ; 
 int LOCKSHARED ; 
 int /*<<< orphan*/  LOOKUP ; 
 int /*<<< orphan*/  NDFREE (struct nameidata*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NDF_ONLY_PNBUF ; 
 int /*<<< orphan*/  NDINIT (struct nameidata*,int /*<<< orphan*/ ,int,int,char const*,struct thread*) ; 
 int /*<<< orphan*/  VOP_UNLOCK (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int change_dir (int /*<<< orphan*/ ,struct thread*) ; 
 int namei (struct nameidata*) ; 
 int /*<<< orphan*/  pwd_chdir (struct thread*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vput (int /*<<< orphan*/ ) ; 

int
kern_chdir(struct thread *td, const char *path, enum uio_seg pathseg)
{
	struct nameidata nd;
	int error;

	NDINIT(&nd, LOOKUP, FOLLOW | LOCKSHARED | LOCKLEAF | AUDITVNODE1,
	    pathseg, path, td);
	if ((error = namei(&nd)) != 0)
		return (error);
	if ((error = change_dir(nd.ni_vp, td)) != 0) {
		vput(nd.ni_vp);
		NDFREE(&nd, NDF_ONLY_PNBUF);
		return (error);
	}
	VOP_UNLOCK(nd.ni_vp, 0);
	NDFREE(&nd, NDF_ONLY_PNBUF);
	pwd_chdir(td, nd.ni_vp);
	return (0);
}