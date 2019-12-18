#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_7__ ;
typedef  struct TYPE_17__   TYPE_6__ ;
typedef  struct TYPE_16__   TYPE_5__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  zfsvfs_t ;
struct TYPE_14__ {int /*<<< orphan*/  z_inherit_type; int /*<<< orphan*/  z_object_type; } ;
typedef  TYPE_3__ zfs_object_ace_t ;
typedef  int /*<<< orphan*/  zfs_fuid_info_t ;
struct TYPE_13__ {size_t (* ace_size ) (TYPE_5__*) ;} ;
struct TYPE_15__ {TYPE_2__ z_ops; } ;
typedef  TYPE_4__ zfs_acl_t ;
struct TYPE_12__ {int z_flags; int z_type; int /*<<< orphan*/  z_access_mask; } ;
struct TYPE_16__ {TYPE_1__ z_hdr; int /*<<< orphan*/  z_fuid; } ;
typedef  TYPE_5__ zfs_ace_t ;
typedef  int /*<<< orphan*/  vtype_t ;
typedef  int uint64_t ;
typedef  int uint16_t ;
typedef  int /*<<< orphan*/  cred_t ;
typedef  size_t caddr_t ;
struct TYPE_17__ {int a_flags; int a_type; int /*<<< orphan*/  a_who; int /*<<< orphan*/  a_access_mask; } ;
typedef  TYPE_6__ ace_t ;
struct TYPE_18__ {int /*<<< orphan*/  a_inherit_obj_type; int /*<<< orphan*/  a_obj_type; } ;
typedef  TYPE_7__ ace_object_t ;

/* Variables and functions */
#define  ACE_ACCESS_ALLOWED_OBJECT_ACE_TYPE 131 
#define  ACE_ACCESS_DENIED_OBJECT_ACE_TYPE 130 
 int ACE_EVERYONE ; 
 int ACE_OWNER ; 
#define  ACE_SYSTEM_ALARM_OBJECT_ACE_TYPE 129 
#define  ACE_SYSTEM_AUDIT_OBJECT_ACE_TYPE 128 
 int ACE_TYPE_FLAGS ; 
 scalar_t__ B_TRUE ; 
 int /*<<< orphan*/  EINVAL ; 
 int OWNING_GROUP ; 
 int SET_ERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ZFS_ACE_GROUP ; 
 int /*<<< orphan*/  ZFS_ACE_USER ; 
 int /*<<< orphan*/  bcopy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 size_t stub1 (TYPE_5__*) ; 
 scalar_t__ zfs_ace_valid (int /*<<< orphan*/ ,TYPE_4__*,int,int) ; 
 int /*<<< orphan*/  zfs_fuid_create (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 

int
zfs_copy_ace_2_fuid(zfsvfs_t *zfsvfs, vtype_t obj_type, zfs_acl_t *aclp,
    void *datap, zfs_ace_t *z_acl, uint64_t aclcnt, size_t *size,
    zfs_fuid_info_t **fuidp, cred_t *cr)
{
	int i;
	uint16_t entry_type;
	zfs_ace_t *aceptr = z_acl;
	ace_t *acep = datap;
	zfs_object_ace_t *zobjacep;
	ace_object_t *aceobjp;

	for (i = 0; i != aclcnt; i++) {
		aceptr->z_hdr.z_access_mask = acep->a_access_mask;
		aceptr->z_hdr.z_flags = acep->a_flags;
		aceptr->z_hdr.z_type = acep->a_type;
		entry_type = aceptr->z_hdr.z_flags & ACE_TYPE_FLAGS;
		if (entry_type != ACE_OWNER && entry_type != OWNING_GROUP &&
		    entry_type != ACE_EVERYONE) {
			aceptr->z_fuid = zfs_fuid_create(zfsvfs, acep->a_who,
			    cr, (entry_type == 0) ?
			    ZFS_ACE_USER : ZFS_ACE_GROUP, fuidp);
		}

		/*
		 * Make sure ACE is valid
		 */
		if (zfs_ace_valid(obj_type, aclp, aceptr->z_hdr.z_type,
		    aceptr->z_hdr.z_flags) != B_TRUE)
			return (SET_ERROR(EINVAL));

		switch (acep->a_type) {
		case ACE_ACCESS_ALLOWED_OBJECT_ACE_TYPE:
		case ACE_ACCESS_DENIED_OBJECT_ACE_TYPE:
		case ACE_SYSTEM_AUDIT_OBJECT_ACE_TYPE:
		case ACE_SYSTEM_ALARM_OBJECT_ACE_TYPE:
			zobjacep = (zfs_object_ace_t *)aceptr;
			aceobjp = (ace_object_t *)acep;

			bcopy(aceobjp->a_obj_type, zobjacep->z_object_type,
			    sizeof (aceobjp->a_obj_type));
			bcopy(aceobjp->a_inherit_obj_type,
			    zobjacep->z_inherit_type,
			    sizeof (aceobjp->a_inherit_obj_type));
			acep = (ace_t *)((caddr_t)acep + sizeof (ace_object_t));
			break;
		default:
			acep = (ace_t *)((caddr_t)acep + sizeof (ace_t));
		}

		aceptr = (zfs_ace_t *)((caddr_t)aceptr +
		    aclp->z_ops.ace_size(aceptr));
	}

	*size = (caddr_t)aceptr - (caddr_t)z_acl;

	return (0);
}