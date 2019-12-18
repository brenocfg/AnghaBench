#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  ecma_object_t ;

/* Variables and functions */
 int /*<<< orphan*/  ECMA_OBJECT_TYPE_GENERAL ; 
 int /*<<< orphan*/ * ecma_create_object (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

ecma_object_t *
ecma_op_create_object_object_noarg_and_set_prototype (ecma_object_t *object_prototype_p) /**< pointer to prototype of
                                                                                              the object
                                                                                              (can be NULL) */
{
  ecma_object_t *obj_p = ecma_create_object (object_prototype_p, 0, ECMA_OBJECT_TYPE_GENERAL);

  /*
   * [[Class]] property of ECMA_OBJECT_TYPE_GENERAL type objects
   * without ECMA_INTERNAL_PROPERTY_CLASS internal property
   * is "Object".
   *
   * See also: ecma_object_get_class_name
   */

  return obj_p;
}