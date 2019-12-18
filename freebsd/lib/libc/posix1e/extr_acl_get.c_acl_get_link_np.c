#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_6__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  acl_type_t ;
typedef  TYPE_1__* acl_t ;
struct TYPE_8__ {int /*<<< orphan*/  acl_maxcnt; } ;
struct TYPE_7__ {TYPE_6__ ats_acl; } ;

/* Variables and functions */
 int /*<<< orphan*/  ACL_MAX_ENTRIES ; 
 int __acl_get_link (char const*,int /*<<< orphan*/ ,TYPE_6__*) ; 
 int /*<<< orphan*/  _acl_brand_from_type (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _acl_type_unold (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  acl_free (TYPE_1__*) ; 
 TYPE_1__* acl_init (int /*<<< orphan*/ ) ; 

acl_t
acl_get_link_np(const char *path_p, acl_type_t type)
{
	acl_t	aclp;
	int	error;

	aclp = acl_init(ACL_MAX_ENTRIES);
	if (aclp == NULL)
		return (NULL);

	type = _acl_type_unold(type);
	error = __acl_get_link(path_p, type, &aclp->ats_acl);
	if (error) {
		acl_free(aclp);
		return (NULL);
	}

	aclp->ats_acl.acl_maxcnt = ACL_MAX_ENTRIES;
	_acl_brand_from_type(aclp, type);

	return (aclp);
}