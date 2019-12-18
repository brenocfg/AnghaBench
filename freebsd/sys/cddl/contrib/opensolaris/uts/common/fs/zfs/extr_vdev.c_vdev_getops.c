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
struct TYPE_4__ {int /*<<< orphan*/  vdev_op_type; } ;
typedef  TYPE_1__ vdev_ops_t ;

/* Variables and functions */
 scalar_t__ strcmp (int /*<<< orphan*/ ,char const*) ; 
 TYPE_1__** vdev_ops_table ; 

__attribute__((used)) static vdev_ops_t *
vdev_getops(const char *type)
{
	vdev_ops_t *ops, **opspp;

	for (opspp = vdev_ops_table; (ops = *opspp) != NULL; opspp++)
		if (strcmp(ops->vdev_op_type, type) == 0)
			break;

	return (ops);
}