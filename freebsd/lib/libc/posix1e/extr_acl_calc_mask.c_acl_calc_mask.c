#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct acl {int acl_cnt; TYPE_1__* acl_entry; } ;
typedef  TYPE_2__* acl_t ;
struct TYPE_11__ {struct acl ats_acl; } ;
struct TYPE_10__ {int ae_tag; int ae_perm; int /*<<< orphan*/  ae_id; } ;

/* Variables and functions */
 int /*<<< orphan*/  ACL_BRAND_POSIX ; 
#define  ACL_GROUP 131 
#define  ACL_GROUP_OBJ 130 
#define  ACL_MASK 129 
 int ACL_MAX_ENTRIES ; 
 int ACL_PERM_BITS ; 
 int /*<<< orphan*/  ACL_UNDEFINED_ID ; 
#define  ACL_USER 128 
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  ENOMEM ; 
 int /*<<< orphan*/  _acl_brand_as (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _acl_brand_may_be (TYPE_2__*,int /*<<< orphan*/ ) ; 
 TYPE_2__* acl_dup (TYPE_2__*) ; 
 int /*<<< orphan*/  acl_free (TYPE_2__*) ; 
 int acl_valid (TYPE_2__*) ; 
 int /*<<< orphan*/  errno ; 

int
acl_calc_mask(acl_t *acl_p)
{
	struct acl	*acl_int, *acl_int_new;
	acl_t		acl_new;
	int		i, mask_mode, mask_num;

	/*
	 * (23.4.2.4) requires acl_p to point to a pointer to a valid ACL.
	 * Since one of the primary reasons to use this function would be
	 * to calculate the appropriate mask to obtain a valid ACL, we only
	 * perform sanity checks here and validate the ACL prior to
	 * returning.
	 */
	if (acl_p == NULL || *acl_p == NULL) {
		errno = EINVAL;
		return (-1);
	}

	if (!_acl_brand_may_be(*acl_p, ACL_BRAND_POSIX)) {
		errno = EINVAL;
		return (-1);
	}
	_acl_brand_as(*acl_p, ACL_BRAND_POSIX);

	acl_int = &(*acl_p)->ats_acl;
	if ((acl_int->acl_cnt < 3) || (acl_int->acl_cnt > ACL_MAX_ENTRIES)) {
		errno = EINVAL;
		return (-1);
	}

	acl_new = acl_dup(*acl_p);
	if (acl_new == NULL)
		return (-1);
	acl_int_new = &acl_new->ats_acl;

	mask_mode = 0;
	mask_num = -1;

	/* gather permissions and find a mask entry */
	for (i = 0; i < acl_int_new->acl_cnt; i++) {
		switch(acl_int_new->acl_entry[i].ae_tag) {
		case ACL_USER:
		case ACL_GROUP:
		case ACL_GROUP_OBJ:
			mask_mode |=
			    acl_int_new->acl_entry[i].ae_perm & ACL_PERM_BITS;
			break;
		case ACL_MASK:
			mask_num = i;
			break;
		}
	}

	/* if a mask entry already exists, overwrite the perms */
	if (mask_num != -1)
		acl_int_new->acl_entry[mask_num].ae_perm = mask_mode;
	else {
		/* if no mask exists, check acl_cnt... */
		if (acl_int_new->acl_cnt == ACL_MAX_ENTRIES) {
			errno = ENOMEM;
			acl_free(acl_new);
			return (-1);
		}
		/* ...and add the mask entry */
		acl_int_new->acl_entry[acl_int_new->acl_cnt].ae_tag = ACL_MASK;
		acl_int_new->acl_entry[acl_int_new->acl_cnt].ae_id =
		    ACL_UNDEFINED_ID;
		acl_int_new->acl_entry[acl_int_new->acl_cnt].ae_perm =
		    mask_mode;
		acl_int_new->acl_cnt++;
	}

	if (acl_valid(acl_new) == -1) {
		errno = EINVAL;
		acl_free(acl_new);
		return (-1);
	}

	**acl_p = *acl_new;
	acl_free(acl_new);

	return (0);
}