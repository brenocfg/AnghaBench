#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  acl_entry_type_t ;
typedef  TYPE_1__* acl_entry_t ;
struct TYPE_4__ {int /*<<< orphan*/  ae_entry_type; } ;

/* Variables and functions */
 int /*<<< orphan*/  ACL_BRAND_NFS4 ; 
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  _entry_brand_may_be (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errno ; 

int
acl_get_entry_type_np(acl_entry_t entry_d, acl_entry_type_t *entry_type_p)
{

	if (entry_d == NULL || entry_type_p == NULL) {
		errno = EINVAL;
		return (-1);
	}

	if (!_entry_brand_may_be(entry_d, ACL_BRAND_NFS4)) {
		errno = EINVAL;
		return (-1);
	}

	*entry_type_p = entry_d->ae_entry_type;

	return (0);
}