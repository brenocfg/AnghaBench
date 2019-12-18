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
struct vnode {int dummy; } ;
struct thread {int dummy; } ;
struct nameidata {struct vnode* ni_vp; } ;
typedef  enum uio_seg { ____Placeholder_uio_seg } uio_seg ;

/* Variables and functions */
 int AUDITVNODE1 ; 
 int EINVAL ; 
 size_t IOSIZE_MAX ; 
 int LOCKLEAF ; 
 int LOCKSHARED ; 
 int /*<<< orphan*/  LOOKUP ; 
 int /*<<< orphan*/  NDFREE (struct nameidata*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NDF_ONLY_PNBUF ; 
 int /*<<< orphan*/  NDINIT_AT (struct nameidata*,int /*<<< orphan*/ ,int,int,char const*,int,struct thread*) ; 
 int NOFOLLOW ; 
 int kern_readlink_vp (struct vnode*,char*,int,size_t,struct thread*) ; 
 int namei (struct nameidata*) ; 
 int /*<<< orphan*/  vput (struct vnode*) ; 

int
kern_readlinkat(struct thread *td, int fd, const char *path,
    enum uio_seg pathseg, char *buf, enum uio_seg bufseg, size_t count)
{
	struct vnode *vp;
	struct nameidata nd;
	int error;

	if (count > IOSIZE_MAX)
		return (EINVAL);

	NDINIT_AT(&nd, LOOKUP, NOFOLLOW | LOCKSHARED | LOCKLEAF | AUDITVNODE1,
	    pathseg, path, fd, td);

	if ((error = namei(&nd)) != 0)
		return (error);
	NDFREE(&nd, NDF_ONLY_PNBUF);
	vp = nd.ni_vp;

	error = kern_readlink_vp(vp, buf, bufseg, count, td);
	vput(vp);

	return (error);
}