#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  ecma_value_t ;
typedef  int /*<<< orphan*/  ecma_object_t ;
struct TYPE_5__ {int item_count; int /*<<< orphan*/ * buffer_p; } ;
typedef  TYPE_1__ ecma_collection_t ;

/* Variables and functions */
 int /*<<< orphan*/  ECMA_IS_VALUE_ERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  JERRY_ASSERT (int) ; 
 int /*<<< orphan*/  ecma_collection_destroy (TYPE_1__*) ; 
 int /*<<< orphan*/  ecma_collection_free_objects (TYPE_1__*) ; 
 int /*<<< orphan*/ * ecma_fast_array_extend (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * ecma_get_object_from_value (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ecma_op_create_array_object (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 TYPE_1__* ecma_op_object_get_property_names (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int ecma_op_object_is_fast_array (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

ecma_value_t
ecma_builtin_helper_object_get_properties (ecma_object_t *obj_p, /**< object */
                                           uint32_t opts) /**< any combination of ecma_list_properties_options_t */
{
  JERRY_ASSERT (obj_p != NULL);

  ecma_value_t new_array = ecma_op_create_array_object (NULL, 0, false);
  JERRY_ASSERT (!ECMA_IS_VALUE_ERROR (new_array));
  ecma_object_t *new_array_p = ecma_get_object_from_value (new_array);

  ecma_collection_t *props_p = ecma_op_object_get_property_names (obj_p, opts);

  if (props_p->item_count == 0)
  {
    ecma_collection_destroy (props_p);
    return new_array;
  }

  JERRY_ASSERT (ecma_op_object_is_fast_array (new_array_p));

  ecma_value_t *buffer_p = props_p->buffer_p;
  ecma_value_t *values_p = ecma_fast_array_extend (new_array_p, props_p->item_count);

  memcpy (values_p, buffer_p, props_p->item_count * sizeof (ecma_value_t));

  ecma_collection_free_objects (props_p);

  return new_array;
}