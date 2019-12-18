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
struct TYPE_2__ {scalar_t__ a_type; scalar_t__ a_id; scalar_t__ a_perm; } ;
typedef  TYPE_1__ aclent_t ;

/* Variables and functions */

int
cmp2acls(void *a, void *b)
{
	aclent_t *x = (aclent_t *)a;
	aclent_t *y = (aclent_t *)b;

	/* Compare types */
	if (x->a_type < y->a_type)
		return (-1);
	if (x->a_type > y->a_type)
		return (1);
	/* Equal types; compare id's */
	if (x->a_id < y->a_id)
		return (-1);
	if (x->a_id > y->a_id)
		return (1);
	/* Equal ids; compare perms */
	if (x->a_perm < y->a_perm)
		return (-1);
	if (x->a_perm > y->a_perm)
		return (1);
	/* Totally equal */
	return (0);
}