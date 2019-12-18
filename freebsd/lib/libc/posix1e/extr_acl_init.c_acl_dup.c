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
typedef  TYPE_1__* acl_t ;
struct TYPE_5__ {scalar_t__ ats_cur_entry; } ;

/* Variables and functions */
 int /*<<< orphan*/  ACL_MAX_ENTRIES ; 
 TYPE_1__* acl_init (int /*<<< orphan*/ ) ; 

acl_t
acl_dup(acl_t acl)
{
	acl_t	acl_new;

	acl_new = acl_init(ACL_MAX_ENTRIES);
	if (acl_new != NULL) {
		*acl_new = *acl;
		acl->ats_cur_entry = 0;
		acl_new->ats_cur_entry = 0;
	}

	return (acl_new);
}