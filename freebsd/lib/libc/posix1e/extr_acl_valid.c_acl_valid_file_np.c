#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  acl_type_t ;
typedef  TYPE_1__* acl_t ;
struct TYPE_5__ {int /*<<< orphan*/  ats_acl; } ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 int __acl_aclcheck_file (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  _acl_type_unold (int /*<<< orphan*/ ) ; 
 scalar_t__ _posix1e_acl (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _posix1e_acl_sort (TYPE_1__*) ; 
 int /*<<< orphan*/  errno ; 

int
acl_valid_file_np(const char *pathp, acl_type_t type, acl_t acl)
{

	if (pathp == NULL || acl == NULL) {
		errno = EINVAL;
		return (-1);
	}
	type = _acl_type_unold(type);
	if (_posix1e_acl(acl, type))
		_posix1e_acl_sort(acl);

	return (__acl_aclcheck_file(pathp, type, &acl->ats_acl));
}