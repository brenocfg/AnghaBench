#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uid_t ;
struct acl_entry {int ae_perm; int ae_tag; int /*<<< orphan*/  ae_id; } ;
struct acl {int acl_cnt; struct acl_entry* acl_entry; } ;
typedef  TYPE_1__* acl_t ;
struct TYPE_3__ {struct acl ats_acl; } ;

/* Variables and functions */
#define  ACL_GROUP 133 
#define  ACL_GROUP_OBJ 132 
#define  ACL_MASK 131 
#define  ACL_OTHER 130 
 int ACL_PERM_BITS ; 
#define  ACL_USER 129 
#define  ACL_USER_OBJ 128 
 int EINVAL ; 

int
_posix1e_acl_check(acl_t acl)
{
	struct acl *acl_int;
	struct acl_entry	*entry; 	/* current entry */
	uid_t	highest_uid=0, highest_gid=0;
	int	stage = ACL_USER_OBJ;
	int	i = 0;
	int	count_user_obj=0, count_user=0, count_group_obj=0,
		count_group=0, count_mask=0, count_other=0;

	acl_int = &acl->ats_acl;

	/* printf("_posix1e_acl_check: checking acl with %d entries\n",
	    acl->acl_cnt); */
	while (i < acl_int->acl_cnt) {
		entry = &acl_int->acl_entry[i];

		if ((entry->ae_perm | ACL_PERM_BITS) != ACL_PERM_BITS)
			return (EINVAL);

		switch(entry->ae_tag) {
		case ACL_USER_OBJ:
			/* printf("_posix1e_acl_check: %d: ACL_USER_OBJ\n",
			    i); */
			if (stage > ACL_USER_OBJ)
				return (EINVAL);
			stage = ACL_USER;
			count_user_obj++;
			break;

		case ACL_USER:
			/* printf("_posix1e_acl_check: %d: ACL_USER\n", i); */
			if (stage > ACL_USER)
				return (EINVAL);
			stage = ACL_USER;
			if (count_user && (entry->ae_id <= highest_uid))
				return (EINVAL);
			highest_uid = entry->ae_id;
			count_user++;
			break;

		case ACL_GROUP_OBJ:
			/* printf("_posix1e_acl_check: %d: ACL_GROUP_OBJ\n",
			    i); */
			if (stage > ACL_GROUP_OBJ)
				return (EINVAL);
			stage = ACL_GROUP;
			count_group_obj++;
			break;

		case ACL_GROUP:
			/* printf("_posix1e_acl_check: %d: ACL_GROUP\n", i); */
			if (stage > ACL_GROUP)
				return (EINVAL);
			stage = ACL_GROUP;
			if (count_group && (entry->ae_id <= highest_gid))
				return (EINVAL);
			highest_gid = entry->ae_id;
			count_group++;
			break;

		case ACL_MASK:
			/* printf("_posix1e_acl_check: %d: ACL_MASK\n", i); */
			if (stage > ACL_MASK)
				return (EINVAL);
			stage = ACL_MASK;
			count_mask++;
			break;

		case ACL_OTHER:
			/* printf("_posix1e_acl_check: %d: ACL_OTHER\n", i); */
			if (stage > ACL_OTHER)
				return (EINVAL);
			stage = ACL_OTHER;
			count_other++;
			break;

		default:
			/* printf("_posix1e_acl_check: %d: INVALID\n", i); */
			return (EINVAL);
		}
		i++;
	}

	if (count_user_obj != 1)
		return (EINVAL);

	if (count_group_obj != 1)
		return (EINVAL);

	if (count_mask != 0 && count_mask != 1)
		return (EINVAL);

	if (count_other != 1)
		return (EINVAL);

	return (0);
}