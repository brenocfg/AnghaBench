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
typedef  void* ecma_value_t ;
typedef  int /*<<< orphan*/  ecma_object_t ;
typedef  int ecma_length_t ;
typedef  int /*<<< orphan*/  ecma_integer_value_t ;
struct TYPE_4__ {void* args_len_or_this; int /*<<< orphan*/  target_function; } ;
struct TYPE_5__ {TYPE_1__ bound_function; } ;
struct TYPE_6__ {TYPE_2__ u; } ;
typedef  TYPE_3__ ecma_extended_object_t ;

/* Variables and functions */
 int /*<<< orphan*/  ECMA_BUILTIN_ID_FUNCTION_PROTOTYPE ; 
 int /*<<< orphan*/  ECMA_OBJECT_TYPE_BOUND_FUNCTION ; 
 int /*<<< orphan*/  ECMA_SET_INTERNAL_VALUE_POINTER (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 void* ECMA_VALUE_UNDEFINED ; 
 int /*<<< orphan*/  JERRY_ASSERT (int) ; 
 int /*<<< orphan*/ * ecma_builtin_get (int /*<<< orphan*/ ) ; 
 void* ecma_copy_value_if_not_object (void* const) ; 
 int /*<<< orphan*/ * ecma_create_object (int /*<<< orphan*/ *,size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ecma_is_value_integer_number (void* const) ; 
 void* ecma_make_integer_value (int /*<<< orphan*/ ) ; 
 void* ecma_make_object_value (int /*<<< orphan*/ *) ; 

__attribute__((used)) static ecma_value_t
ecma_builtin_function_prototype_object_bind (ecma_object_t *this_arg_obj_p , /**< this argument object */
                                             const ecma_value_t *arguments_list_p, /**< list of arguments */
                                             ecma_length_t arguments_number) /**< number of arguments */
{
  /* 4. 11. 18. */
  ecma_object_t *prototype_obj_p = ecma_builtin_get (ECMA_BUILTIN_ID_FUNCTION_PROTOTYPE);

  ecma_object_t *function_p;
  ecma_extended_object_t *ext_function_p;

  if (arguments_number == 0
      || (arguments_number == 1 && !ecma_is_value_integer_number (arguments_list_p[0])))
  {
    function_p = ecma_create_object (prototype_obj_p,
                                     sizeof (ecma_extended_object_t),
                                     ECMA_OBJECT_TYPE_BOUND_FUNCTION);

    /* 8. */
    ext_function_p = (ecma_extended_object_t *) function_p;
    ECMA_SET_INTERNAL_VALUE_POINTER (ext_function_p->u.bound_function.target_function,
                                     this_arg_obj_p);

    ext_function_p->u.bound_function.args_len_or_this = ECMA_VALUE_UNDEFINED;

    if (arguments_number != 0)
    {
      ext_function_p->u.bound_function.args_len_or_this = ecma_copy_value_if_not_object (arguments_list_p[0]);
    }
  }
  else
  {
    JERRY_ASSERT (arguments_number > 0);

    size_t obj_size = sizeof (ecma_extended_object_t) + (arguments_number * sizeof (ecma_value_t));

    function_p = ecma_create_object (prototype_obj_p,
                                     obj_size,
                                     ECMA_OBJECT_TYPE_BOUND_FUNCTION);

    /* 8. */
    ext_function_p = (ecma_extended_object_t *) function_p;
    ECMA_SET_INTERNAL_VALUE_POINTER (ext_function_p->u.bound_function.target_function,
                                     this_arg_obj_p);

    /* NOTE: This solution provides temporary false data about the object's size
       but prevents GC from freeing it until it's not fully initialized. */
    ext_function_p->u.bound_function.args_len_or_this = ECMA_VALUE_UNDEFINED;
    ecma_value_t *args_p = (ecma_value_t *) (ext_function_p + 1);

    for (ecma_length_t i = 0; i < arguments_number; i++)
    {
      *args_p++ = ecma_copy_value_if_not_object (arguments_list_p[i]);
    }

    ecma_value_t args_len_or_this = ecma_make_integer_value ((ecma_integer_value_t) arguments_number);
    ext_function_p->u.bound_function.args_len_or_this = args_len_or_this;
  }

  /*
   * [[Class]] property is not stored explicitly for objects of ECMA_OBJECT_TYPE_FUNCTION type.
   *
   * See also: ecma_object_get_class_name
   */

  /* 22. */
  return ecma_make_object_value (function_p);
}