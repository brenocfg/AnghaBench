#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
struct TYPE_14__ {scalar_t__ z_acl_inherit; } ;
typedef  TYPE_2__ zfsvfs_t ;
struct TYPE_13__ {size_t (* ace_size ) (void*) ;size_t (* ace_data ) (void*,void**) ;scalar_t__ (* ace_flags_get ) (void*) ;int /*<<< orphan*/  (* ace_flags_set ) (void*,scalar_t__) ;} ;
struct TYPE_15__ {TYPE_1__ z_ops; int /*<<< orphan*/  z_hints; int /*<<< orphan*/  z_acl_bytes; int /*<<< orphan*/  z_acl_count; int /*<<< orphan*/  z_acl; int /*<<< orphan*/  z_version; } ;
typedef  TYPE_3__ zfs_acl_t ;
struct TYPE_16__ {scalar_t__ z_size; int /*<<< orphan*/  z_ace_count; void* z_acldata; } ;
typedef  TYPE_4__ zfs_acl_node_t ;
typedef  scalar_t__ vtype_t ;
typedef  scalar_t__ uint_t ;
typedef  int uint64_t ;
typedef  int /*<<< orphan*/  uint32_t ;
typedef  scalar_t__ uint16_t ;
typedef  int boolean_t ;

/* Variables and functions */
 scalar_t__ ACE_DIRECTORY_INHERIT_ACE ; 
 scalar_t__ ACE_EVERYONE ; 
 int /*<<< orphan*/  ACE_EXECUTE ; 
 scalar_t__ ACE_FILE_INHERIT_ACE ; 
 scalar_t__ ACE_INHERITED_ACE ; 
 scalar_t__ ACE_INHERIT_ONLY_ACE ; 
 scalar_t__ ACE_NO_PROPAGATE_INHERIT_ACE ; 
 scalar_t__ ACE_OWNER ; 
 scalar_t__ ALLOW ; 
 scalar_t__ ALL_INHERIT ; 
 int B_FALSE ; 
 int B_TRUE ; 
 scalar_t__ OWNING_GROUP ; 
 int /*<<< orphan*/  RESTRICTED_CLEAR ; 
 int S_IXGRP ; 
 int S_IXOTH ; 
 int S_IXUSR ; 
 scalar_t__ VDIR ; 
 int /*<<< orphan*/  VERIFY (int) ; 
 scalar_t__ VLNK ; 
 scalar_t__ VREG ; 
 scalar_t__ ZFS_ACL_DISCARD ; 
 scalar_t__ ZFS_ACL_NOALLOW ; 
 scalar_t__ ZFS_ACL_PASSTHROUGH ; 
 scalar_t__ ZFS_ACL_PASSTHROUGH_X ; 
 scalar_t__ ZFS_ACL_RESTRICTED ; 
 int /*<<< orphan*/  ZFS_INHERIT_ACE ; 
 int /*<<< orphan*/  bcopy (void*,void*,size_t) ; 
 int /*<<< orphan*/  list_insert_tail (int /*<<< orphan*/ *,TYPE_4__*) ; 
 size_t stub1 (void*) ; 
 size_t stub2 (void*,void**) ; 
 size_t stub3 (void*,void**) ; 
 scalar_t__ stub4 (void*) ; 
 int /*<<< orphan*/  stub5 (void*,scalar_t__) ; 
 int /*<<< orphan*/  stub6 (void*,scalar_t__) ; 
 int /*<<< orphan*/  stub7 (void*,scalar_t__) ; 
 int /*<<< orphan*/  zfs_ace_can_use (scalar_t__,scalar_t__) ; 
 TYPE_3__* zfs_acl_alloc (int /*<<< orphan*/ ) ; 
 void* zfs_acl_next_ace (TYPE_3__*,void*,int*,int /*<<< orphan*/ *,scalar_t__*,scalar_t__*) ; 
 TYPE_4__* zfs_acl_node_alloc (size_t) ; 
 int /*<<< orphan*/  zfs_acl_valid_ace_type (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  zfs_set_ace (TYPE_3__*,void*,int /*<<< orphan*/ ,scalar_t__,int,scalar_t__) ; 

__attribute__((used)) static zfs_acl_t *
zfs_acl_inherit(zfsvfs_t *zfsvfs, vtype_t vtype, zfs_acl_t *paclp,
    uint64_t mode, boolean_t *need_chmod)
{
	void		*pacep = NULL;
	void		*acep;
	zfs_acl_node_t  *aclnode;
	zfs_acl_t	*aclp = NULL;
	uint64_t	who;
	uint32_t	access_mask;
	uint16_t	iflags, newflags, type;
	size_t		ace_size;
	void		*data1, *data2;
	size_t		data1sz, data2sz;
	uint_t		aclinherit;
	boolean_t	isdir = (vtype == VDIR);
	boolean_t	isreg = (vtype == VREG);

	*need_chmod = B_TRUE;

	aclp = zfs_acl_alloc(paclp->z_version);
	aclinherit = zfsvfs->z_acl_inherit;
	if (aclinherit == ZFS_ACL_DISCARD || vtype == VLNK)
		return (aclp);

	while (pacep = zfs_acl_next_ace(paclp, pacep, &who,
	    &access_mask, &iflags, &type)) {

		/*
		 * don't inherit bogus ACEs
		 */
		if (!zfs_acl_valid_ace_type(type, iflags))
			continue;

		/*
		 * Check if ACE is inheritable by this vnode
		 */
		if ((aclinherit == ZFS_ACL_NOALLOW && type == ALLOW) ||
		    !zfs_ace_can_use(vtype, iflags))
			continue;

		/*
		 * If owner@, group@, or everyone@ inheritable
		 * then zfs_acl_chmod() isn't needed.
		 */
		if ((aclinherit == ZFS_ACL_PASSTHROUGH ||
		    aclinherit == ZFS_ACL_PASSTHROUGH_X) &&
		    ((iflags & (ACE_OWNER|ACE_EVERYONE)) ||
		    ((iflags & OWNING_GROUP) == OWNING_GROUP)) &&
		    (isreg || (isdir && (iflags & ACE_DIRECTORY_INHERIT_ACE))))
			*need_chmod = B_FALSE;

		/*
		 * Strip inherited execute permission from file if
		 * not in mode
		 */
		if (aclinherit == ZFS_ACL_PASSTHROUGH_X && type == ALLOW &&
		    !isdir && ((mode & (S_IXUSR|S_IXGRP|S_IXOTH)) == 0)) {
			access_mask &= ~ACE_EXECUTE;
		}

		/*
		 * Strip write_acl and write_owner from permissions
		 * when inheriting an ACE
		 */
		if (aclinherit == ZFS_ACL_RESTRICTED && type == ALLOW) {
			access_mask &= ~RESTRICTED_CLEAR;
		}

		ace_size = aclp->z_ops.ace_size(pacep);
		aclnode = zfs_acl_node_alloc(ace_size);
		list_insert_tail(&aclp->z_acl, aclnode);
		acep = aclnode->z_acldata;

		zfs_set_ace(aclp, acep, access_mask, type,
		    who, iflags|ACE_INHERITED_ACE);

		/*
		 * Copy special opaque data if any
		 */
		if ((data1sz = paclp->z_ops.ace_data(pacep, &data1)) != 0) {
			VERIFY((data2sz = aclp->z_ops.ace_data(acep,
			    &data2)) == data1sz);
			bcopy(data1, data2, data2sz);
		}

		aclp->z_acl_count++;
		aclnode->z_ace_count++;
		aclp->z_acl_bytes += aclnode->z_size;
		newflags = aclp->z_ops.ace_flags_get(acep);

		/*
		 * If ACE is not to be inherited further, or if the vnode is
		 * not a directory, remove all inheritance flags
		 */
		if (!isdir || (iflags & ACE_NO_PROPAGATE_INHERIT_ACE)) {
			newflags &= ~ALL_INHERIT;
			aclp->z_ops.ace_flags_set(acep,
			    newflags|ACE_INHERITED_ACE);
			continue;
		}

		/*
		 * This directory has an inheritable ACE
		 */
		aclp->z_hints |= ZFS_INHERIT_ACE;

		/*
		 * If only FILE_INHERIT is set then turn on
		 * inherit_only
		 */
		if ((iflags & (ACE_FILE_INHERIT_ACE |
		    ACE_DIRECTORY_INHERIT_ACE)) == ACE_FILE_INHERIT_ACE) {
			newflags |= ACE_INHERIT_ONLY_ACE;
			aclp->z_ops.ace_flags_set(acep,
			    newflags|ACE_INHERITED_ACE);
		} else {
			newflags &= ~ACE_INHERIT_ONLY_ACE;
			aclp->z_ops.ace_flags_set(acep,
			    newflags|ACE_INHERITED_ACE);
		}
	}

	return (aclp);
}