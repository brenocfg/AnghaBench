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
struct vnstat {scalar_t__ vn_mode; int /*<<< orphan*/  vn_size; int /*<<< orphan*/  vn_fileid; int /*<<< orphan*/  vn_fsid; } ;
struct vnode {int v_type; } ;
struct TYPE_2__ {scalar_t__ va_mode; int /*<<< orphan*/  va_fileid; int /*<<< orphan*/  va_fsid; } ;
struct nfsnode {TYPE_1__ n_vattr; int /*<<< orphan*/  n_size; } ;
typedef  int /*<<< orphan*/  nfsnode ;
typedef  scalar_t__ mode_t ;
typedef  int /*<<< orphan*/  kvm_t ;

/* Variables and functions */
 scalar_t__ S_IFBLK ; 
 scalar_t__ S_IFCHR ; 
 scalar_t__ S_IFDIR ; 
 scalar_t__ S_IFIFO ; 
 scalar_t__ S_IFLNK ; 
 scalar_t__ S_IFREG ; 
 scalar_t__ S_IFSOCK ; 
#define  VBLK 134 
#define  VCHR 133 
#define  VDIR 132 
#define  VFIFO 131 
#define  VLNK 130 
#define  VREG 129 
#define  VSOCK 128 
 scalar_t__ VTONFS (struct vnode*) ; 
 int /*<<< orphan*/  kvm_read_all (int /*<<< orphan*/ *,unsigned long,struct nfsnode*,int) ; 
 int /*<<< orphan*/  warnx (char*,void*) ; 

int
nfs_filestat(kvm_t *kd, struct vnode *vp, struct vnstat *vn)
{
	struct nfsnode nfsnode;
	mode_t mode;

	if (!kvm_read_all(kd, (unsigned long)VTONFS(vp), &nfsnode,
	    sizeof(nfsnode))) {
		warnx("can't read nfsnode at %p",
		    (void *)VTONFS(vp));
		return (1);
	}
	vn->vn_fsid = nfsnode.n_vattr.va_fsid;
	vn->vn_fileid = nfsnode.n_vattr.va_fileid;
	vn->vn_size = nfsnode.n_size;
	mode = (mode_t)nfsnode.n_vattr.va_mode;
	switch (vp->v_type) {
	case VREG:
		mode |= S_IFREG;
		break;
	case VDIR:
		mode |= S_IFDIR;
		break;
	case VBLK:
		mode |= S_IFBLK;
		break;
	case VCHR:
		mode |= S_IFCHR;
		break;
	case VLNK:
		mode |= S_IFLNK;
		break;
	case VSOCK:
		mode |= S_IFSOCK;
		break;
	case VFIFO:
		mode |= S_IFIFO;
		break;
	default:
		break;
	};
	vn->vn_mode = mode;
	return (0);
}