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
struct acl {int /*<<< orphan*/  acl_maxcnt; } ;

/* Variables and functions */
 int /*<<< orphan*/  ACL_MAX_ENTRIES ; 
 int /*<<< orphan*/  M_ACL ; 
 struct acl* malloc (int,int /*<<< orphan*/ ,int) ; 

struct acl *
acl_alloc(int flags)
{
	struct acl *aclp;

	aclp = malloc(sizeof(*aclp), M_ACL, flags);
	if (aclp == NULL)
		return (NULL);

	aclp->acl_maxcnt = ACL_MAX_ENTRIES;

	return (aclp);
}