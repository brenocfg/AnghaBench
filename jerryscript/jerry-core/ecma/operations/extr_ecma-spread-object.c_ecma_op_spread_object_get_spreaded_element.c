#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ecma_value_t ;
typedef  int /*<<< orphan*/  ecma_object_t ;
struct TYPE_5__ {int /*<<< orphan*/  spread_value; } ;
struct TYPE_6__ {TYPE_1__ u2; } ;
struct TYPE_7__ {TYPE_2__ pseudo_array; } ;
struct TYPE_8__ {TYPE_3__ u; } ;
typedef  TYPE_4__ ecma_extended_object_t ;

/* Variables and functions */
 int /*<<< orphan*/  JERRY_ASSERT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ecma_copy_value (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ecma_make_object_value (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ecma_op_is_spread_object (int /*<<< orphan*/ ) ; 

ecma_value_t
ecma_op_spread_object_get_spreaded_element (ecma_object_t *object_p) /**< spread object */
{
  JERRY_ASSERT (ecma_op_is_spread_object (ecma_make_object_value (object_p)));

  ecma_extended_object_t *ext_object_p = (ecma_extended_object_t *) object_p;
  return ecma_copy_value (ext_object_p->u.pseudo_array.u2.spread_value);
}