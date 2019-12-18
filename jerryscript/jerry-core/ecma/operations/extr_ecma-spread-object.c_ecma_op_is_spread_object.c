#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ecma_value_t ;
typedef  int /*<<< orphan*/  ecma_object_t ;
struct TYPE_4__ {scalar_t__ type; } ;
struct TYPE_5__ {TYPE_1__ pseudo_array; } ;
struct TYPE_6__ {TYPE_2__ u; } ;
typedef  TYPE_3__ ecma_extended_object_t ;

/* Variables and functions */
 scalar_t__ ECMA_OBJECT_TYPE_PSEUDO_ARRAY ; 
 scalar_t__ ECMA_PSEUDO_SPREAD_OBJECT ; 
 int /*<<< orphan*/ * ecma_get_object_from_value (int /*<<< orphan*/ ) ; 
 scalar_t__ ecma_get_object_type (int /*<<< orphan*/ *) ; 
 scalar_t__ ecma_is_value_object (int /*<<< orphan*/ ) ; 

bool
ecma_op_is_spread_object (ecma_value_t value) /**< value to check */
{
  if (ecma_is_value_object (value))
  {
    ecma_object_t *object_p = ecma_get_object_from_value (value);

    if (ecma_get_object_type (object_p) == ECMA_OBJECT_TYPE_PSEUDO_ARRAY)
    {
      ecma_extended_object_t *ext_object_p = (ecma_extended_object_t *) object_p;
      return ext_object_p->u.pseudo_array.type == ECMA_PSEUDO_SPREAD_OBJECT;
    }
  }

  return false;
}