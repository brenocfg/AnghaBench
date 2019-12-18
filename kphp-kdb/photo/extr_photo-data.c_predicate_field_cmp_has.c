#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {TYPE_1__* field; } ;
typedef  TYPE_2__ predicate_field_cmp ;
struct TYPE_8__ {int /*<<< orphan*/ * obj; int /*<<< orphan*/ * dyn; } ;
typedef  TYPE_3__ actual_object ;
struct TYPE_6__ {int /*<<< orphan*/  id; } ;

/* Variables and functions */
 scalar_t__ has_field (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int predicate_field_cmp_has (predicate_field_cmp *self, actual_object *ao) {
  return (ao->dyn != NULL && has_field (ao->dyn, self->field->id)) ||
         (ao->obj != NULL && has_field (ao->obj, self->field->id));
}