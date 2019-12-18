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
typedef  TYPE_1__* acl_entry_t ;
struct TYPE_3__ {int ae_tag; int /*<<< orphan*/  ae_id; } ;

/* Variables and functions */
#define  ACL_GROUP 129 
#define  ACL_USER 128 
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  errno ; 

int
acl_set_qualifier(acl_entry_t entry_d, const void *tag_qualifier_p)
{

	if (!entry_d || !tag_qualifier_p) {
		errno = EINVAL;
		return (-1);
	}
	switch(entry_d->ae_tag) {
	case ACL_USER:
	case ACL_GROUP:
		entry_d->ae_id = *(uid_t *)tag_qualifier_p;
		break;
	default:
		errno = EINVAL;
		return (-1);
	}

	return (0);
}