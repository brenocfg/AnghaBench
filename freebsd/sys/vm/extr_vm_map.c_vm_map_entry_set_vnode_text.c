#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_4__* vm_object_t ;
typedef  TYPE_5__* vm_map_entry_t ;
struct vnode {int dummy; } ;
struct TYPE_9__ {TYPE_4__* vm_object; } ;
struct TYPE_13__ {int eflags; TYPE_1__ object; } ;
struct TYPE_10__ {struct vnode* swp_tmpfs; } ;
struct TYPE_11__ {TYPE_2__ swp; } ;
struct TYPE_12__ {scalar_t__ type; int flags; TYPE_3__ un_pager; struct vnode* handle; struct TYPE_12__* backing_object; } ;

/* Variables and functions */
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int LK_RETRY ; 
 int LK_SHARED ; 
 int MAP_ENTRY_IS_SUB_MAP ; 
 int MAP_ENTRY_VN_EXEC ; 
 scalar_t__ OBJT_DEAD ; 
 scalar_t__ OBJT_SWAP ; 
 scalar_t__ OBJT_VNODE ; 
 int OBJ_TMPFS ; 
 int OBJ_TMPFS_NODE ; 
 int /*<<< orphan*/  VM_OBJECT_RLOCK (TYPE_4__*) ; 
 int /*<<< orphan*/  VM_OBJECT_RUNLOCK (TYPE_4__*) ; 
 int /*<<< orphan*/  VOP_SET_TEXT_CHECKED (struct vnode*) ; 
 int /*<<< orphan*/  VOP_UNLOCK (struct vnode*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VOP_UNSET_TEXT_CHECKED (struct vnode*) ; 
 int /*<<< orphan*/  vdrop (struct vnode*) ; 
 int /*<<< orphan*/  vhold (struct vnode*) ; 
 int /*<<< orphan*/  vn_lock (struct vnode*,int) ; 

void
vm_map_entry_set_vnode_text(vm_map_entry_t entry, bool add)
{
	vm_object_t object, object1;
	struct vnode *vp;

	if ((entry->eflags & MAP_ENTRY_VN_EXEC) == 0)
		return;
	KASSERT((entry->eflags & MAP_ENTRY_IS_SUB_MAP) == 0,
	    ("Submap with execs"));
	object = entry->object.vm_object;
	KASSERT(object != NULL, ("No object for text, entry %p", entry));
	VM_OBJECT_RLOCK(object);
	while ((object1 = object->backing_object) != NULL) {
		VM_OBJECT_RLOCK(object1);
		VM_OBJECT_RUNLOCK(object);
		object = object1;
	}

	vp = NULL;
	if (object->type == OBJT_DEAD) {
		/*
		 * For OBJT_DEAD objects, v_writecount was handled in
		 * vnode_pager_dealloc().
		 */
	} else if (object->type == OBJT_VNODE) {
		vp = object->handle;
	} else if (object->type == OBJT_SWAP) {
		KASSERT((object->flags & OBJ_TMPFS_NODE) != 0,
		    ("vm_map_entry_set_vnode_text: swap and !TMPFS "
		    "entry %p, object %p, add %d", entry, object, add));
		/*
		 * Tmpfs VREG node, which was reclaimed, has
		 * OBJ_TMPFS_NODE flag set, but not OBJ_TMPFS.  In
		 * this case there is no v_writecount to adjust.
		 */
		if ((object->flags & OBJ_TMPFS) != 0)
			vp = object->un_pager.swp.swp_tmpfs;
	} else {
		KASSERT(0,
		    ("vm_map_entry_set_vnode_text: wrong object type, "
		    "entry %p, object %p, add %d", entry, object, add));
	}
	if (vp != NULL) {
		if (add) {
			VOP_SET_TEXT_CHECKED(vp);
			VM_OBJECT_RUNLOCK(object);
		} else {
			vhold(vp);
			VM_OBJECT_RUNLOCK(object);
			vn_lock(vp, LK_SHARED | LK_RETRY);
			VOP_UNSET_TEXT_CHECKED(vp);
			VOP_UNLOCK(vp, 0);
			vdrop(vp);
		}
	} else {
		VM_OBJECT_RUNLOCK(object);
	}
}