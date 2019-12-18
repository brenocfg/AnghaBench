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
typedef  int /*<<< orphan*/  vm_object_t ;
typedef  int /*<<< orphan*/  uid_t ;
struct TYPE_4__ {int /*<<< orphan*/  tn_aobj; } ;
struct TYPE_3__ {struct tmpfs_node* tn_parent; int /*<<< orphan*/ * tn_readdir_lastp; int /*<<< orphan*/  tn_readdir_lastn; int /*<<< orphan*/  tn_dupindex; int /*<<< orphan*/  tn_dirhead; } ;
struct tmpfs_node {int tn_type; int tn_refcount; int tn_attached; TYPE_2__ tn_reg; int /*<<< orphan*/  tn_size; int /*<<< orphan*/  tn_link; TYPE_1__ tn_dir; int /*<<< orphan*/  tn_links; scalar_t__ tn_rdev; int /*<<< orphan*/  tn_id; int /*<<< orphan*/  tn_mode; int /*<<< orphan*/  tn_gid; int /*<<< orphan*/  tn_uid; int /*<<< orphan*/  tn_atime; int /*<<< orphan*/  tn_mtime; int /*<<< orphan*/  tn_ctime; int /*<<< orphan*/  tn_birthtime; } ;
struct tmpfs_mount {scalar_t__ tm_nodes_inuse; scalar_t__ tm_nodes_max; int /*<<< orphan*/  tm_refcount; int /*<<< orphan*/  tm_nodes_used; int /*<<< orphan*/ * tm_root; int /*<<< orphan*/  tm_ino_unr; int /*<<< orphan*/  tm_node_pool; } ;
struct mount {int mnt_kern_flag; } ;
typedef  int /*<<< orphan*/  mode_t ;
typedef  int /*<<< orphan*/  gid_t ;
typedef  enum vtype { ____Placeholder_vtype } vtype ;
typedef  scalar_t__ dev_t ;

/* Variables and functions */
 int EBUSY ; 
 int ENOSPC ; 
 int EROFS ; 
 int IFF (int,int) ; 
 int IMPLIES (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  LIST_INIT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LIST_INSERT_HEAD (int /*<<< orphan*/ *,struct tmpfs_node*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MAXPATHLEN ; 
 int MNTK_UNMOUNT ; 
 int MNT_RDONLY ; 
 int /*<<< orphan*/  MPASS (int) ; 
 int /*<<< orphan*/  M_TMPFSNAME ; 
 int /*<<< orphan*/  M_WAITOK ; 
 int /*<<< orphan*/  OBJT_SWAP ; 
 int OBJ_NOSPLIT ; 
 int /*<<< orphan*/  OBJ_ONEMAPPING ; 
 int OBJ_TMPFS_NODE ; 
 int /*<<< orphan*/  RB_INIT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TMPFS_LOCK (struct tmpfs_mount*) ; 
 int /*<<< orphan*/  TMPFS_NODE_LOCK (struct tmpfs_node*) ; 
 int /*<<< orphan*/  TMPFS_NODE_UNLOCK (struct tmpfs_node*) ; 
 int /*<<< orphan*/  TMPFS_UNLOCK (struct tmpfs_mount*) ; 
#define  VBLK 134 
#define  VCHR 133 
#define  VDIR 132 
#define  VFIFO 131 
#define  VLNK 130 
 int /*<<< orphan*/  VM_OBJECT_WLOCK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VM_OBJECT_WUNLOCK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VM_PROT_DEFAULT ; 
 scalar_t__ VNOVAL ; 
#define  VREG 129 
#define  VSOCK 128 
 int /*<<< orphan*/  alloc_unr64 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  malloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  panic (char*,struct tmpfs_node*,int) ; 
 int /*<<< orphan*/  strlen (char const*) ; 
 scalar_t__ tmpfs_pages_check_avail (struct tmpfs_mount*,int) ; 
 int /*<<< orphan*/  tn_entries ; 
 scalar_t__ uma_zalloc_arg (int /*<<< orphan*/ ,struct tmpfs_mount*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vfs_timestamp (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vm_object_clear_flag (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vm_object_set_flag (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  vm_pager_allocate (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int
tmpfs_alloc_node(struct mount *mp, struct tmpfs_mount *tmp, enum vtype type,
    uid_t uid, gid_t gid, mode_t mode, struct tmpfs_node *parent,
    const char *target, dev_t rdev, struct tmpfs_node **node)
{
	struct tmpfs_node *nnode;
	vm_object_t obj;

	/* If the root directory of the 'tmp' file system is not yet
	 * allocated, this must be the request to do it. */
	MPASS(IMPLIES(tmp->tm_root == NULL, parent == NULL && type == VDIR));

	MPASS(IFF(type == VLNK, target != NULL));
	MPASS(IFF(type == VBLK || type == VCHR, rdev != VNOVAL));

	if (tmp->tm_nodes_inuse >= tmp->tm_nodes_max)
		return (ENOSPC);
	if (tmpfs_pages_check_avail(tmp, 1) == 0)
		return (ENOSPC);

	if ((mp->mnt_kern_flag & MNTK_UNMOUNT) != 0) {
		/*
		 * When a new tmpfs node is created for fully
		 * constructed mount point, there must be a parent
		 * node, which vnode is locked exclusively.  As
		 * consequence, if the unmount is executing in
		 * parallel, vflush() cannot reclaim the parent vnode.
		 * Due to this, the check for MNTK_UNMOUNT flag is not
		 * racy: if we did not see MNTK_UNMOUNT flag, then tmp
		 * cannot be destroyed until node construction is
		 * finished and the parent vnode unlocked.
		 *
		 * Tmpfs does not need to instantiate new nodes during
		 * unmount.
		 */
		return (EBUSY);
	}
	if ((mp->mnt_kern_flag & MNT_RDONLY) != 0)
		return (EROFS);

	nnode = (struct tmpfs_node *)uma_zalloc_arg(tmp->tm_node_pool, tmp,
	    M_WAITOK);

	/* Generic initialization. */
	nnode->tn_type = type;
	vfs_timestamp(&nnode->tn_atime);
	nnode->tn_birthtime = nnode->tn_ctime = nnode->tn_mtime =
	    nnode->tn_atime;
	nnode->tn_uid = uid;
	nnode->tn_gid = gid;
	nnode->tn_mode = mode;
	nnode->tn_id = alloc_unr64(&tmp->tm_ino_unr);
	nnode->tn_refcount = 1;

	/* Type-specific initialization. */
	switch (nnode->tn_type) {
	case VBLK:
	case VCHR:
		nnode->tn_rdev = rdev;
		break;

	case VDIR:
		RB_INIT(&nnode->tn_dir.tn_dirhead);
		LIST_INIT(&nnode->tn_dir.tn_dupindex);
		MPASS(parent != nnode);
		MPASS(IMPLIES(parent == NULL, tmp->tm_root == NULL));
		nnode->tn_dir.tn_parent = (parent == NULL) ? nnode : parent;
		nnode->tn_dir.tn_readdir_lastn = 0;
		nnode->tn_dir.tn_readdir_lastp = NULL;
		nnode->tn_links++;
		TMPFS_NODE_LOCK(nnode->tn_dir.tn_parent);
		nnode->tn_dir.tn_parent->tn_links++;
		TMPFS_NODE_UNLOCK(nnode->tn_dir.tn_parent);
		break;

	case VFIFO:
		/* FALLTHROUGH */
	case VSOCK:
		break;

	case VLNK:
		MPASS(strlen(target) < MAXPATHLEN);
		nnode->tn_size = strlen(target);
		nnode->tn_link = malloc(nnode->tn_size, M_TMPFSNAME,
		    M_WAITOK);
		memcpy(nnode->tn_link, target, nnode->tn_size);
		break;

	case VREG:
		obj = nnode->tn_reg.tn_aobj =
		    vm_pager_allocate(OBJT_SWAP, NULL, 0, VM_PROT_DEFAULT, 0,
			NULL /* XXXKIB - tmpfs needs swap reservation */);
		VM_OBJECT_WLOCK(obj);
		/* OBJ_TMPFS is set together with the setting of vp->v_object */
		vm_object_set_flag(obj, OBJ_NOSPLIT | OBJ_TMPFS_NODE);
		vm_object_clear_flag(obj, OBJ_ONEMAPPING);
		VM_OBJECT_WUNLOCK(obj);
		break;

	default:
		panic("tmpfs_alloc_node: type %p %d", nnode,
		    (int)nnode->tn_type);
	}

	TMPFS_LOCK(tmp);
	LIST_INSERT_HEAD(&tmp->tm_nodes_used, nnode, tn_entries);
	nnode->tn_attached = true;
	tmp->tm_nodes_inuse++;
	tmp->tm_refcount++;
	TMPFS_UNLOCK(tmp);

	*node = nnode;
	return (0);
}