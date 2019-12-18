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
typedef  int /*<<< orphan*/  ecma_string_t ;
typedef  int /*<<< orphan*/  ecma_standard_error_t ;
struct TYPE_3__ {int /*<<< orphan*/  value; } ;
typedef  TYPE_1__ ecma_property_value_t ;
typedef  int /*<<< orphan*/  ecma_object_t ;

/* Variables and functions */
 int /*<<< orphan*/  ECMA_PROPERTY_CONFIGURABLE_WRITABLE ; 
 int /*<<< orphan*/  LIT_MAGIC_STRING_MESSAGE ; 
 TYPE_1__* ecma_create_named_data_property (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ecma_get_magic_string (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ecma_make_string_value (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * ecma_new_standard_error (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ecma_ref_ecma_string (int /*<<< orphan*/ *) ; 

ecma_object_t *
ecma_new_standard_error_with_message (ecma_standard_error_t error_type, /**< native error type */
                                      ecma_string_t *message_string_p) /**< message string */
{
  ecma_object_t *new_error_obj_p = ecma_new_standard_error (error_type);

  ecma_property_value_t *prop_value_p;
  prop_value_p = ecma_create_named_data_property (new_error_obj_p,
                                                  ecma_get_magic_string (LIT_MAGIC_STRING_MESSAGE),
                                                  ECMA_PROPERTY_CONFIGURABLE_WRITABLE,
                                                  NULL);

  ecma_ref_ecma_string (message_string_p);
  prop_value_p->value = ecma_make_string_value (message_string_p);

  return new_error_obj_p;
}