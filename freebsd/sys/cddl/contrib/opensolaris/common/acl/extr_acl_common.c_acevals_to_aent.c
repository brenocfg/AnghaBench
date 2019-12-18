#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
typedef  scalar_t__ uid_t ;
typedef  scalar_t__ gid_t ;
typedef  scalar_t__ boolean_t ;
struct TYPE_7__ {int a_type; scalar_t__ a_id; int /*<<< orphan*/  a_perm; } ;
typedef  TYPE_1__ aclent_t ;
struct TYPE_8__ {int allowed; int denied; scalar_t__ mask; int aent_type; scalar_t__ key; } ;
typedef  TYPE_2__ acevals_t ;
struct TYPE_9__ {scalar_t__ acl_mask; scalar_t__ hasmask; } ;
typedef  TYPE_3__ ace_list_t ;

/* Variables and functions */
 int ACE_DELETE_CHILD ; 
 int ACE_POSIX_SUPPORTED_BITS ; 
 int EINVAL ; 
 int ENOTSUP ; 
 int GROUP ; 
 int GROUP_OBJ ; 
 int OTHER_OBJ ; 
 int USER ; 
 int USER_OBJ ; 
 int ace_allow_to_mode (int,int /*<<< orphan*/ *,scalar_t__) ; 

__attribute__((used)) static int
acevals_to_aent(acevals_t *vals, aclent_t *dest, ace_list_t *list,
    uid_t owner, gid_t group, boolean_t isdir)
{
	int error;
	uint32_t  flips = ACE_POSIX_SUPPORTED_BITS;

	if (isdir)
		flips |= ACE_DELETE_CHILD;
	if (vals->allowed != (vals->denied ^ flips)) {
		error = ENOTSUP;
		goto out;
	}
	if ((list->hasmask) && (list->acl_mask != vals->mask) &&
	    (vals->aent_type & (USER | GROUP | GROUP_OBJ))) {
		error = ENOTSUP;
		goto out;
	}
	error = ace_allow_to_mode(vals->allowed, &dest->a_perm, isdir);
	if (error != 0)
		goto out;
	dest->a_type = vals->aent_type;
	if (dest->a_type & (USER | GROUP)) {
		dest->a_id = vals->key;
	} else if (dest->a_type & USER_OBJ) {
		dest->a_id = owner;
	} else if (dest->a_type & GROUP_OBJ) {
		dest->a_id = group;
	} else if (dest->a_type & OTHER_OBJ) {
		dest->a_id = 0;
	} else {
		error = EINVAL;
		goto out;
	}

out:
	return (error);
}