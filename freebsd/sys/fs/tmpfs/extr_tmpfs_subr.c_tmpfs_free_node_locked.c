#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_2__* vm_object_t ;
struct TYPE_4__ {TYPE_2__* tn_aobj; } ;
struct tmpfs_node {scalar_t__ tn_refcount; int tn_attached; int tn_vpstate; int tn_type; TYPE_1__ tn_reg; int /*<<< orphan*/  tn_link; int /*<<< orphan*/ * tn_vnode; } ;
struct tmpfs_mount {scalar_t__ tm_nodes_inuse; int /*<<< orphan*/  tm_node_pool; int /*<<< orphan*/  tm_pages_used; } ;
struct TYPE_5__ {int flags; int /*<<< orphan*/  size; } ;

/* Variables and functions */
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int /*<<< orphan*/  LIST_REMOVE (struct tmpfs_node*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MPASS (int) ; 
 int /*<<< orphan*/  M_TMPFSNAME ; 
 int OBJ_TMPFS ; 
 int /*<<< orphan*/  TMPFS_LOCK (struct tmpfs_mount*) ; 
 int /*<<< orphan*/  TMPFS_MP_ASSERT_LOCKED (struct tmpfs_mount*) ; 
 int /*<<< orphan*/  TMPFS_NODE_ASSERT_LOCKED (struct tmpfs_node*) ; 
 int /*<<< orphan*/  TMPFS_NODE_UNLOCK (struct tmpfs_node*) ; 
 int /*<<< orphan*/  TMPFS_UNLOCK (struct tmpfs_mount*) ; 
 int TMPFS_VNODE_ALLOCATING ; 
#define  VBLK 134 
#define  VCHR 133 
#define  VDIR 132 
#define  VFIFO 131 
#define  VLNK 130 
#define  VREG 129 
#define  VSOCK 128 
 int /*<<< orphan*/  atomic_subtract_long (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  panic (char*,struct tmpfs_node*,int) ; 
 int /*<<< orphan*/  tmpfs_free_tmp (struct tmpfs_mount*) ; 
 int /*<<< orphan*/  tn_entries ; 
 int /*<<< orphan*/  uma_zfree (int /*<<< orphan*/ ,struct tmpfs_node*) ; 
 int /*<<< orphan*/  vm_object_deallocate (TYPE_2__*) ; 

bool
tmpfs_free_node_locked(struct tmpfs_mount *tmp, struct tmpfs_node *node,
    bool detach)
{
	vm_object_t uobj;

	TMPFS_MP_ASSERT_LOCKED(tmp);
	TMPFS_NODE_ASSERT_LOCKED(node);
	KASSERT(node->tn_refcount > 0, ("node %p refcount zero", node));

	node->tn_refcount--;
	if (node->tn_attached && (detach || node->tn_refcount == 0)) {
		MPASS(tmp->tm_nodes_inuse > 0);
		tmp->tm_nodes_inuse--;
		LIST_REMOVE(node, tn_entries);
		node->tn_attached = false;
	}
	if (node->tn_refcount > 0)
		return (false);

#ifdef INVARIANTS
	MPASS(node->tn_vnode == NULL);
	MPASS((node->tn_vpstate & TMPFS_VNODE_ALLOCATING) == 0);
#endif
	TMPFS_NODE_UNLOCK(node);
	TMPFS_UNLOCK(tmp);

	switch (node->tn_type) {
	case VBLK:
		/* FALLTHROUGH */
	case VCHR:
		/* FALLTHROUGH */
	case VDIR:
		/* FALLTHROUGH */
	case VFIFO:
		/* FALLTHROUGH */
	case VSOCK:
		break;

	case VLNK:
		free(node->tn_link, M_TMPFSNAME);
		break;

	case VREG:
		uobj = node->tn_reg.tn_aobj;
		if (uobj != NULL) {
			if (uobj->size != 0)
				atomic_subtract_long(&tmp->tm_pages_used, uobj->size);
			KASSERT((uobj->flags & OBJ_TMPFS) == 0,
			    ("leaked OBJ_TMPFS node %p vm_obj %p", node, uobj));
			vm_object_deallocate(uobj);
		}
		break;

	default:
		panic("tmpfs_free_node: type %p %d", node, (int)node->tn_type);
	}

	uma_zfree(tmp->tm_node_pool, node);
	TMPFS_LOCK(tmp);
	tmpfs_free_tmp(tmp);
	return (true);
}