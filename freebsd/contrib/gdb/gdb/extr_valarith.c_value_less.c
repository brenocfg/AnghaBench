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
typedef  enum type_code { ____Placeholder_type_code } type_code ;
typedef  scalar_t__ CORE_ADDR ;

/* Variables and functions */
 int /*<<< orphan*/  BINOP_LESS ; 
 int /*<<< orphan*/  COERCE_NUMBER (struct value*) ; 
 int TYPE_CODE (struct type*) ; 
 int TYPE_CODE_BOOL ; 
 int TYPE_CODE_FLT ; 
 int TYPE_CODE_INT ; 
 int TYPE_CODE_PTR ; 
 int TYPE_CODE_STRING ; 
 int /*<<< orphan*/  VALUE_TYPE (struct value*) ; 
 struct type* check_typedef (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  error (char*) ; 
 int longest_to_int (scalar_t__) ; 
 scalar_t__ value_as_address (struct value*) ; 
 scalar_t__ value_as_double (struct value*) ; 
 scalar_t__ value_as_long (struct value*) ; 
 struct value* value_binop (struct value*,struct value*,int /*<<< orphan*/ ) ; 
 scalar_t__ value_strcmp (struct value*,struct value*) ; 

int
value_less (struct value *arg1, struct value *arg2)
{
  enum type_code code1;
  enum type_code code2;
  struct type *type1, *type2;

  COERCE_NUMBER (arg1);
  COERCE_NUMBER (arg2);

  type1 = check_typedef (VALUE_TYPE (arg1));
  type2 = check_typedef (VALUE_TYPE (arg2));
  code1 = TYPE_CODE (type1);
  code2 = TYPE_CODE (type2);

  if ((code1 == TYPE_CODE_INT || code1 == TYPE_CODE_BOOL) &&
      (code2 == TYPE_CODE_INT || code2 == TYPE_CODE_BOOL))
    return longest_to_int (value_as_long (value_binop (arg1, arg2,
						       BINOP_LESS)));
  else if ((code1 == TYPE_CODE_FLT || code1 == TYPE_CODE_INT || code1 == TYPE_CODE_BOOL)
	   && (code2 == TYPE_CODE_FLT || code2 == TYPE_CODE_INT || code2 == TYPE_CODE_BOOL))
    return value_as_double (arg1) < value_as_double (arg2);
  else if (code1 == TYPE_CODE_PTR && code2 == TYPE_CODE_PTR)
    return value_as_address (arg1) < value_as_address (arg2);

  /* FIXME: Need to promote to either CORE_ADDR or LONGEST, whichever
     is bigger.  */
  else if (code1 == TYPE_CODE_PTR && (code2 == TYPE_CODE_INT || code2 == TYPE_CODE_BOOL))
    return value_as_address (arg1) < (CORE_ADDR) value_as_long (arg2);
  else if (code2 == TYPE_CODE_PTR && (code1 == TYPE_CODE_INT || code1 == TYPE_CODE_BOOL))
    return (CORE_ADDR) value_as_long (arg1) < value_as_address (arg2);
  else if (code1 == TYPE_CODE_STRING && code2 == TYPE_CODE_STRING)
    return value_strcmp (arg1, arg2) < 0;
  else
    {
      error ("Invalid type combination in ordering comparison.");
      return 0;
    }
}