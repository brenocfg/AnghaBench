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
typedef  int /*<<< orphan*/  acl_tag_t ;
typedef  TYPE_1__* acl_entry_t ;
struct TYPE_3__ {int /*<<< orphan*/  ae_tag; } ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  errno ; 

int
acl_get_tag_type(acl_entry_t entry_d, acl_tag_t *tag_type_p)
{

	if (entry_d == NULL || tag_type_p == NULL) {
		errno = EINVAL;
		return (-1);
	}

	*tag_type_p = entry_d->ae_tag;

	return (0);
}