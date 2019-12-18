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
struct TYPE_3__ {scalar_t__ everyone; scalar_t__ group; scalar_t__ owner; scalar_t__ deny2; scalar_t__ deny1; scalar_t__ allow0; } ;
typedef  TYPE_1__ trivial_acl_t ;
typedef  int /*<<< orphan*/  mode_t ;
typedef  int /*<<< orphan*/  boolean_t ;
typedef  int /*<<< orphan*/  ace_t ;

/* Variables and functions */
 int /*<<< orphan*/  ACE_ACCESS_ALLOWED_ACE_TYPE ; 
 int /*<<< orphan*/  ACE_ACCESS_DENIED_ACE_TYPE ; 
 int ACE_EVERYONE ; 
 int ACE_GROUP ; 
 int ACE_IDENTIFIER_GROUP ; 
 int ACE_OWNER ; 
 int /*<<< orphan*/  SET_ACE (int /*<<< orphan*/ **,int,int,scalar_t__,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  acl_trivial_access_masks (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int cacl_malloc (void**,int) ; 

int
acl_trivial_create(mode_t mode, boolean_t isdir, ace_t **acl, int *count)
{
	int		index = 0;
	int		error;
	trivial_acl_t	masks;

	*count = 3;
	acl_trivial_access_masks(mode, isdir, &masks);

	if (masks.allow0)
		(*count)++;
	if (masks.deny1)
		(*count)++;
	if (masks.deny2)
		(*count)++;

	if ((error = cacl_malloc((void **)acl, *count * sizeof (ace_t))) != 0)
		return (error);

	if (masks.allow0) {
		SET_ACE(acl, index, -1, masks.allow0,
		    ACE_ACCESS_ALLOWED_ACE_TYPE, ACE_OWNER);
	}
	if (masks.deny1) {
		SET_ACE(acl, index, -1, masks.deny1,
		    ACE_ACCESS_DENIED_ACE_TYPE, ACE_OWNER);
	}
	if (masks.deny2) {
		SET_ACE(acl, index, -1, masks.deny2,
		    ACE_ACCESS_DENIED_ACE_TYPE, ACE_GROUP|ACE_IDENTIFIER_GROUP);
	}

	SET_ACE(acl, index, -1, masks.owner, ACE_ACCESS_ALLOWED_ACE_TYPE,
	    ACE_OWNER);
	SET_ACE(acl, index, -1, masks.group, ACE_ACCESS_ALLOWED_ACE_TYPE,
	    ACE_IDENTIFIER_GROUP|ACE_GROUP);
	SET_ACE(acl, index, -1, masks.everyone, ACE_ACCESS_ALLOWED_ACE_TYPE,
	    ACE_EVERYONE);

	return (0);
}