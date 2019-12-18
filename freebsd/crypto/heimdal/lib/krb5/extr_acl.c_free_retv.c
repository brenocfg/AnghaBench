#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/ ** retv; } ;
struct acl_field {scalar_t__ type; struct acl_field* next; TYPE_1__ u; } ;

/* Variables and functions */
 scalar_t__ acl_retval ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
free_retv(struct acl_field *acl)
{
    while(acl != NULL) {
	if (acl->type == acl_retval) {
	    if (*acl->u.retv)
		free(*acl->u.retv);
	    *acl->u.retv = NULL;
	}
	acl = acl->next;
    }
}