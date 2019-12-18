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
struct value {int dummy; } ;
struct type {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  COERCE_ENUM (struct value*) ; 
 int /*<<< orphan*/  COERCE_REF (struct value*) ; 
 scalar_t__ TYPE_CODE (struct type*) ; 
 scalar_t__ TYPE_CODE_BOOL ; 
 scalar_t__ TYPE_CODE_FLT ; 
 scalar_t__ TYPE_CODE_INT ; 
 scalar_t__ TYPE_LENGTH (struct type*) ; 
 struct type* VALUE_TYPE (struct value*) ; 
 struct type* builtin_type_int ; 
 struct type* check_typedef (struct type*) ; 
 int /*<<< orphan*/  error (char*) ; 
 int /*<<< orphan*/  value_as_double (struct value*) ; 
 int /*<<< orphan*/  value_as_long (struct value*) ; 
 struct value* value_from_double (struct type*,int /*<<< orphan*/ ) ; 
 struct value* value_from_longest (struct type*,int /*<<< orphan*/ ) ; 

struct value *
value_neg (struct value *arg1)
{
  struct type *type;
  struct type *result_type = VALUE_TYPE (arg1);

  COERCE_REF (arg1);
  COERCE_ENUM (arg1);

  type = check_typedef (VALUE_TYPE (arg1));

  if (TYPE_CODE (type) == TYPE_CODE_FLT)
    return value_from_double (result_type, -value_as_double (arg1));
  else if (TYPE_CODE (type) == TYPE_CODE_INT || TYPE_CODE (type) == TYPE_CODE_BOOL)
    {
      /* Perform integral promotion for ANSI C/C++.  FIXME: What about
         FORTRAN and (the deleted) chill ?  */
      if (TYPE_LENGTH (type) < TYPE_LENGTH (builtin_type_int))
	result_type = builtin_type_int;

      return value_from_longest (result_type, -value_as_long (arg1));
    }
  else
    {
      error ("Argument to negate operation not a number.");
      return 0;			/* For lint -- never reached */
    }
}