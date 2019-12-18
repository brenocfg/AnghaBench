#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
typedef  int /*<<< orphan*/  uid_t ;
typedef  int /*<<< orphan*/  gid_t ;
typedef  int /*<<< orphan*/  boolean_t ;
struct TYPE_13__ {int a_type; scalar_t__ a_id; int /*<<< orphan*/  a_perm; } ;
typedef  TYPE_1__ aclent_t ;
struct TYPE_14__ {int aent_type; int allowed; } ;
typedef  TYPE_2__ acevals_t ;
struct TYPE_15__ {int seen; scalar_t__ numusers; scalar_t__ numgroups; int dfacl_flag; int acl_mask; TYPE_2__ other_obj; TYPE_2__ group_obj; scalar_t__ hasmask; int /*<<< orphan*/  group; int /*<<< orphan*/  user; TYPE_2__ user_obj; } ;
typedef  TYPE_3__ ace_list_t ;

/* Variables and functions */
 int ACE_DELETE_CHILD ; 
 int ACE_POSIX_SUPPORTED_BITS ; 
 TYPE_2__* AVL_NEXT (int /*<<< orphan*/ *,TYPE_2__*) ; 
 int CLASS_OBJ ; 
 int EINVAL ; 
 int ENOMEM ; 
 int ENOTSUP ; 
 int GROUP ; 
 int GROUP_OBJ ; 
 int OTHER_OBJ ; 
 int USER ; 
 int USER_OBJ ; 
 int ace_mask_to_mode (int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int acevals_to_aent (TYPE_2__*,TYPE_1__*,TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_2__* avl_first (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cacl_free (TYPE_1__*,int) ; 
 scalar_t__ cacl_malloc (void**,int) ; 

__attribute__((used)) static int
ace_list_to_aent(ace_list_t *list, aclent_t **aclentp, int *aclcnt,
    uid_t owner, gid_t group, boolean_t isdir)
{
	int error = 0;
	aclent_t *aent, *result = NULL;
	acevals_t *vals;
	int resultcount;

	if ((list->seen & (USER_OBJ | GROUP_OBJ | OTHER_OBJ)) !=
	    (USER_OBJ | GROUP_OBJ | OTHER_OBJ)) {
		error = ENOTSUP;
		goto out;
	}
	if ((! list->hasmask) && (list->numusers + list->numgroups > 0)) {
		error = ENOTSUP;
		goto out;
	}

	resultcount = 3 + list->numusers + list->numgroups;
	/*
	 * This must be the same condition as below, when we add the CLASS_OBJ
	 * (aka ACL mask)
	 */
	if ((list->hasmask) || (! list->dfacl_flag))
		resultcount += 1;

	if (cacl_malloc((void **)&result,
	    resultcount * sizeof (aclent_t)) != 0) {
		error = ENOMEM;
		goto out;
	}
	aent = result;

	/* USER_OBJ */
	if (!(list->user_obj.aent_type & USER_OBJ)) {
		error = EINVAL;
		goto out;
	}

	error = acevals_to_aent(&list->user_obj, aent, list, owner, group,
	    isdir);

	if (error != 0)
		goto out;
	++aent;
	/* USER */
	vals = NULL;
	for (vals = avl_first(&list->user); vals != NULL;
	    vals = AVL_NEXT(&list->user, vals)) {
		if (!(vals->aent_type & USER)) {
			error = EINVAL;
			goto out;
		}
		error = acevals_to_aent(vals, aent, list, owner, group,
		    isdir);
		if (error != 0)
			goto out;
		++aent;
	}
	/* GROUP_OBJ */
	if (!(list->group_obj.aent_type & GROUP_OBJ)) {
		error = EINVAL;
		goto out;
	}
	error = acevals_to_aent(&list->group_obj, aent, list, owner, group,
	    isdir);
	if (error != 0)
		goto out;
	++aent;
	/* GROUP */
	vals = NULL;
	for (vals = avl_first(&list->group); vals != NULL;
	    vals = AVL_NEXT(&list->group, vals)) {
		if (!(vals->aent_type & GROUP)) {
			error = EINVAL;
			goto out;
		}
		error = acevals_to_aent(vals, aent, list, owner, group,
		    isdir);
		if (error != 0)
			goto out;
		++aent;
	}
	/*
	 * CLASS_OBJ (aka ACL_MASK)
	 *
	 * An ACL_MASK is not fabricated if the ACL is a default ACL.
	 * This is to follow UFS's behavior.
	 */
	if ((list->hasmask) || (! list->dfacl_flag)) {
		if (list->hasmask) {
			uint32_t flips = ACE_POSIX_SUPPORTED_BITS;
			if (isdir)
				flips |= ACE_DELETE_CHILD;
			error = ace_mask_to_mode(list->acl_mask ^ flips,
			    &aent->a_perm, isdir);
			if (error != 0)
				goto out;
		} else {
			/* fabricate the ACL_MASK from the group permissions */
			error = ace_mask_to_mode(list->group_obj.allowed,
			    &aent->a_perm, isdir);
			if (error != 0)
				goto out;
		}
		aent->a_id = 0;
		aent->a_type = CLASS_OBJ | list->dfacl_flag;
		++aent;
	}
	/* OTHER_OBJ */
	if (!(list->other_obj.aent_type & OTHER_OBJ)) {
		error = EINVAL;
		goto out;
	}
	error = acevals_to_aent(&list->other_obj, aent, list, owner, group,
	    isdir);
	if (error != 0)
		goto out;
	++aent;

	*aclentp = result;
	*aclcnt = resultcount;

out:
	if (error != 0) {
		if (result != NULL)
			cacl_free(result, resultcount * sizeof (aclent_t));
	}

	return (error);
}