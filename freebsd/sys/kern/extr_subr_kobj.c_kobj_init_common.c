#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* kobj_t ;
typedef  TYPE_2__* kobj_class_t ;
struct TYPE_6__ {int /*<<< orphan*/  refs; int /*<<< orphan*/  ops; } ;
struct TYPE_5__ {int /*<<< orphan*/  ops; } ;

/* Variables and functions */

__attribute__((used)) static void
kobj_init_common(kobj_t obj, kobj_class_t cls)
{

	obj->ops = cls->ops;
	cls->refs++;
}