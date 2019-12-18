#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int acl_tag_t ;
typedef  int /*<<< orphan*/ * acl_t ;
typedef  int /*<<< orphan*/  acl_entry_t ;

/* Variables and functions */
 scalar_t__ ACL_BRAND_POSIX ; 
 int ACL_FIRST_ENTRY ; 
#define  ACL_GROUP_OBJ 131 
#define  ACL_MASK 130 
 int /*<<< orphan*/  ACL_MAX_ENTRIES ; 
 int ACL_NEXT_ENTRY ; 
#define  ACL_OTHER 129 
 int ACL_UNDEFINED_TAG ; 
#define  ACL_USER_OBJ 128 
 scalar_t__ _acl_brand (int /*<<< orphan*/ *) ; 
 scalar_t__ _entry_brand (int /*<<< orphan*/ ) ; 
 int acl_calc_mask (int /*<<< orphan*/ **) ; 
 int acl_copy_entry (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int acl_create_entry (int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * acl_dup (int /*<<< orphan*/ * const) ; 
 int /*<<< orphan*/  acl_free (int /*<<< orphan*/ *) ; 
 int acl_get_entry (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 int acl_get_tag_type (int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/ * acl_init (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert (int) ; 

__attribute__((used)) static acl_t
_posix1e_acl_strip_np(const acl_t aclp, int recalculate_mask)
{
	acl_t acl_new, acl_old;
	acl_entry_t entry, entry_new;
	acl_tag_t tag;
	int entry_id, have_mask_entry;

	assert(_acl_brand(aclp) == ACL_BRAND_POSIX);

	acl_old = acl_dup(aclp);
	if (acl_old == NULL)
		return (NULL);

	assert(_acl_brand(acl_old) == ACL_BRAND_POSIX);

	have_mask_entry = 0;
	acl_new = acl_init(ACL_MAX_ENTRIES);
	if (acl_new == NULL) {
		acl_free(acl_old);
		return (NULL);
	}
	tag = ACL_UNDEFINED_TAG;

	/* only save the default user/group/other entries */
	entry_id = ACL_FIRST_ENTRY;
	while (acl_get_entry(acl_old, entry_id, &entry) == 1) {
		entry_id = ACL_NEXT_ENTRY;

		assert(_entry_brand(entry) == ACL_BRAND_POSIX);

		if (acl_get_tag_type(entry, &tag) == -1)
			goto fail;

		switch(tag) {
		case ACL_USER_OBJ:
		case ACL_GROUP_OBJ:
		case ACL_OTHER:
			if (acl_create_entry(&acl_new, &entry_new) == -1)
				goto fail;
			if (acl_copy_entry(entry_new, entry) == -1)
				goto fail;
			assert(_entry_brand(entry_new) == ACL_BRAND_POSIX);
			break;
		case ACL_MASK:
			have_mask_entry = 1;
			break;
		default:
			break;
		}
	}

	assert(_acl_brand(acl_new) == ACL_BRAND_POSIX);

	if (have_mask_entry && recalculate_mask) {
		if (acl_calc_mask(&acl_new) == -1)
			goto fail;
	}

	return (acl_new);

fail:
	acl_free(acl_new);
	acl_free(acl_old);

	return (NULL);
}