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
struct acl {int acl_cnt; TYPE_1__* acl_entry; } ;
struct TYPE_2__ {int ae_tag; void* ae_id; int ae_perm; } ;

/* Variables and functions */
#define  ACL_GROUP 133 
#define  ACL_GROUP_OBJ 132 
#define  ACL_MASK 131 
 int ACL_MAX_ENTRIES ; 
#define  ACL_OTHER 130 
 int ACL_PERM_BITS ; 
 void* ACL_UNDEFINED_ID ; 
#define  ACL_USER 129 
#define  ACL_USER_OBJ 128 
 int EINVAL ; 

int
acl_posix1e_check(struct acl *acl)
{
	int num_acl_user_obj, num_acl_user, num_acl_group_obj, num_acl_group;
	int num_acl_mask, num_acl_other, i;

	/*
	 * Verify that the number of entries does not exceed the maximum
	 * defined for acl_t.
	 *
	 * Verify that the correct number of various sorts of ae_tags are
	 * present:
	 *   Exactly one ACL_USER_OBJ
	 *   Exactly one ACL_GROUP_OBJ
	 *   Exactly one ACL_OTHER
	 *   If any ACL_USER or ACL_GROUP entries appear, then exactly one
	 *   ACL_MASK entry must also appear.
	 *
	 * Verify that all ae_perm entries are in ACL_PERM_BITS.
	 *
	 * Verify all ae_tag entries are understood by this implementation.
	 *
	 * Note: Does not check for uniqueness of qualifier (ae_id) field.
	 */
	num_acl_user_obj = num_acl_user = num_acl_group_obj = num_acl_group =
	    num_acl_mask = num_acl_other = 0;
	if (acl->acl_cnt > ACL_MAX_ENTRIES)
		return (EINVAL);
	for (i = 0; i < acl->acl_cnt; i++) {
		/*
		 * Check for a valid tag.
		 */
		switch(acl->acl_entry[i].ae_tag) {
		case ACL_USER_OBJ:
			acl->acl_entry[i].ae_id = ACL_UNDEFINED_ID; /* XXX */
			if (acl->acl_entry[i].ae_id != ACL_UNDEFINED_ID)
				return (EINVAL);
			num_acl_user_obj++;
			break;
		case ACL_GROUP_OBJ:
			acl->acl_entry[i].ae_id = ACL_UNDEFINED_ID; /* XXX */
			if (acl->acl_entry[i].ae_id != ACL_UNDEFINED_ID)
				return (EINVAL);
			num_acl_group_obj++;
			break;
		case ACL_USER:
			if (acl->acl_entry[i].ae_id == ACL_UNDEFINED_ID)
				return (EINVAL);
			num_acl_user++;
			break;
		case ACL_GROUP:
			if (acl->acl_entry[i].ae_id == ACL_UNDEFINED_ID)
				return (EINVAL);
			num_acl_group++;
			break;
		case ACL_OTHER:
			acl->acl_entry[i].ae_id = ACL_UNDEFINED_ID; /* XXX */
			if (acl->acl_entry[i].ae_id != ACL_UNDEFINED_ID)
				return (EINVAL);
			num_acl_other++;
			break;
		case ACL_MASK:
			acl->acl_entry[i].ae_id = ACL_UNDEFINED_ID; /* XXX */
			if (acl->acl_entry[i].ae_id != ACL_UNDEFINED_ID)
				return (EINVAL);
			num_acl_mask++;
			break;
		default:
			return (EINVAL);
		}
		/*
		 * Check for valid perm entries.
		 */
		if ((acl->acl_entry[i].ae_perm | ACL_PERM_BITS) !=
		    ACL_PERM_BITS)
			return (EINVAL);
	}
	if ((num_acl_user_obj != 1) || (num_acl_group_obj != 1) ||
	    (num_acl_other != 1) || (num_acl_mask != 0 && num_acl_mask != 1))
		return (EINVAL);
	if (((num_acl_group != 0) || (num_acl_user != 0)) &&
	    (num_acl_mask != 1))
		return (EINVAL);
	return (0);
}