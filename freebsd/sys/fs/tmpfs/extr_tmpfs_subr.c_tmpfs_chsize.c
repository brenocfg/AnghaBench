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
typedef  int /*<<< orphan*/  u_quad_t ;
struct vnode {int v_type; TYPE_1__* v_mount; } ;
struct ucred {int dummy; } ;
struct tmpfs_node {int tn_flags; } ;
struct thread {int dummy; } ;
struct TYPE_2__ {int mnt_flag; } ;

/* Variables and functions */
 int APPEND ; 
 int /*<<< orphan*/  ASSERT_VOP_ELOCKED (struct vnode*,char*) ; 
 int EISDIR ; 
 int EOPNOTSUPP ; 
 int EPERM ; 
 int EROFS ; 
 int IMMUTABLE ; 
 int MNT_RDONLY ; 
#define  VBLK 132 
#define  VCHR 131 
#define  VDIR 130 
#define  VFIFO 129 
 struct tmpfs_node* VP_TO_TMPFS_NODE (struct vnode*) ; 
#define  VREG 128 
 int tmpfs_truncate (struct vnode*,int /*<<< orphan*/ ) ; 

int
tmpfs_chsize(struct vnode *vp, u_quad_t size, struct ucred *cred,
    struct thread *p)
{
	int error;
	struct tmpfs_node *node;

	ASSERT_VOP_ELOCKED(vp, "chsize");

	node = VP_TO_TMPFS_NODE(vp);

	/* Decide whether this is a valid operation based on the file type. */
	error = 0;
	switch (vp->v_type) {
	case VDIR:
		return EISDIR;

	case VREG:
		if (vp->v_mount->mnt_flag & MNT_RDONLY)
			return EROFS;
		break;

	case VBLK:
		/* FALLTHROUGH */
	case VCHR:
		/* FALLTHROUGH */
	case VFIFO:
		/* Allow modifications of special files even if in the file
		 * system is mounted read-only (we are not modifying the
		 * files themselves, but the objects they represent). */
		return 0;

	default:
		/* Anything else is unsupported. */
		return EOPNOTSUPP;
	}

	/* Immutable or append-only files cannot be modified, either. */
	if (node->tn_flags & (IMMUTABLE | APPEND))
		return EPERM;

	error = tmpfs_truncate(vp, size);
	/* tmpfs_truncate will raise the NOTE_EXTEND and NOTE_ATTRIB kevents
	 * for us, as will update tn_status; no need to do that here. */

	ASSERT_VOP_ELOCKED(vp, "chsize2");

	return (error);
}