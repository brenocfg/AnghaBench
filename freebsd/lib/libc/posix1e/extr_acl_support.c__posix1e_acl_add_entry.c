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
struct acl_entry {int /*<<< orphan*/  ae_id; int /*<<< orphan*/  ae_tag; int /*<<< orphan*/  ae_perm; } ;
struct acl {size_t acl_cnt; struct acl_entry* acl_entry; } ;
typedef  int /*<<< orphan*/  acl_tag_t ;
typedef  TYPE_1__* acl_t ;
typedef  int /*<<< orphan*/  acl_perm_t ;
struct TYPE_3__ {struct acl ats_acl; } ;

/* Variables and functions */
 size_t ACL_MAX_ENTRIES ; 
 int /*<<< orphan*/  ENOMEM ; 
 int /*<<< orphan*/  errno ; 

int
_posix1e_acl_add_entry(acl_t acl, acl_tag_t tag, uid_t id, acl_perm_t perm)
{
	struct acl		*acl_int;
	struct acl_entry	*e;

	acl_int = &acl->ats_acl;

	if (acl_int->acl_cnt >= ACL_MAX_ENTRIES) {
		errno = ENOMEM;
		return (-1);
	}

	e = &(acl_int->acl_entry[acl_int->acl_cnt]);
	e->ae_perm = perm;
	e->ae_tag = tag;
	e->ae_id = id;
	acl_int->acl_cnt++;

	return (0);
}