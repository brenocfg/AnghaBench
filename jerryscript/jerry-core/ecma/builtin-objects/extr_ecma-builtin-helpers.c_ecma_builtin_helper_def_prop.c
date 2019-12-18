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
typedef  int uint32_t ;
typedef  scalar_t__ uint16_t ;
typedef  int /*<<< orphan*/  ecma_value_t ;
typedef  int /*<<< orphan*/  ecma_string_t ;
struct TYPE_3__ {int /*<<< orphan*/  value; scalar_t__ flags; } ;
typedef  TYPE_1__ ecma_property_descriptor_t ;
typedef  int /*<<< orphan*/  ecma_object_t ;

/* Variables and functions */
 int ECMA_NAME_DATA_PROPERTY_DESCRIPTOR_BITS ; 
 int /*<<< orphan*/  ecma_op_object_define_own_property (int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_1__*) ; 

ecma_value_t
ecma_builtin_helper_def_prop (ecma_object_t *obj_p, /**< object */
                              ecma_string_t *index_p, /**< index string */
                              ecma_value_t value, /**< value */
                              uint32_t opts) /**< any combination of ecma_property_flag_t bits
                                              *   with the optional ECMA_IS_THROW flag */
{
  ecma_property_descriptor_t prop_desc;

  prop_desc.flags = (uint16_t) (ECMA_NAME_DATA_PROPERTY_DESCRIPTOR_BITS | opts);

  prop_desc.value = value;

  return ecma_op_object_define_own_property (obj_p,
                                             index_p,
                                             &prop_desc);
}