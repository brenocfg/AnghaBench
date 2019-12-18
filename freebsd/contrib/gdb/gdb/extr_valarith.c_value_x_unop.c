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
typedef  enum noside { ____Placeholder_noside } noside ;
typedef  enum exp_opcode { ____Placeholder_exp_opcode } exp_opcode ;

/* Variables and functions */
 int /*<<< orphan*/  COERCE_ENUM (struct value*) ; 
 int /*<<< orphan*/  COERCE_REF (struct value*) ; 
 int EVAL_AVOID_SIDE_EFFECTS ; 
 scalar_t__ TYPE_CODE (int /*<<< orphan*/ ) ; 
 scalar_t__ TYPE_CODE_STRUCT ; 
 struct type* TYPE_TARGET_TYPE (int /*<<< orphan*/ ) ; 
#define  UNOP_COMPLEMENT 135 
#define  UNOP_IND 134 
#define  UNOP_LOGICAL_NOT 133 
#define  UNOP_NEG 132 
#define  UNOP_POSTDECREMENT 131 
#define  UNOP_POSTINCREMENT 130 
#define  UNOP_PREDECREMENT 129 
#define  UNOP_PREINCREMENT 128 
 int /*<<< orphan*/  VALUE_LVAL (struct value*) ; 
 int /*<<< orphan*/  VALUE_TYPE (struct value*) ; 
 scalar_t__ alloca (int) ; 
 int /*<<< orphan*/  builtin_type_int ; 
 struct value* call_function_by_hand (struct value*,int,struct value**) ; 
 int /*<<< orphan*/  check_typedef (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  error (char*,...) ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 
 struct value* value_addr (struct value*) ; 
 struct value* value_from_longest (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct value* value_struct_elt (struct value**,struct value**,char*,int*,char*) ; 
 struct value* value_zero (struct type*,int /*<<< orphan*/ ) ; 

struct value *
value_x_unop (struct value *arg1, enum exp_opcode op, enum noside noside)
{
  struct value **argvec;
  char *ptr, *mangle_ptr;
  char tstr[13], mangle_tstr[13];
  int static_memfuncp, nargs;

  COERCE_REF (arg1);
  COERCE_ENUM (arg1);

  /* now we know that what we have to do is construct our
     arg vector and find the right function to call it with.  */

  if (TYPE_CODE (check_typedef (VALUE_TYPE (arg1))) != TYPE_CODE_STRUCT)
    error ("Can't do that unary op on that type");	/* FIXME be explicit */

  argvec = (struct value **) alloca (sizeof (struct value *) * 4);
  argvec[1] = value_addr (arg1);
  argvec[2] = 0;

  nargs = 1;

  /* make the right function name up */
  strcpy (tstr, "operator__");
  ptr = tstr + 8;
  strcpy (mangle_tstr, "__");
  mangle_ptr = mangle_tstr + 2;
  switch (op)
    {
    case UNOP_PREINCREMENT:
      strcpy (ptr, "++");
      break;
    case UNOP_PREDECREMENT:
      strcpy (ptr, "--");
      break;
    case UNOP_POSTINCREMENT:
      strcpy (ptr, "++");
      argvec[2] = value_from_longest (builtin_type_int, 0);
      argvec[3] = 0;
      nargs ++;
      break;
    case UNOP_POSTDECREMENT:
      strcpy (ptr, "--");
      argvec[2] = value_from_longest (builtin_type_int, 0);
      argvec[3] = 0;
      nargs ++;
      break;
    case UNOP_LOGICAL_NOT:
      strcpy (ptr, "!");
      break;
    case UNOP_COMPLEMENT:
      strcpy (ptr, "~");
      break;
    case UNOP_NEG:
      strcpy (ptr, "-");
      break;
    case UNOP_IND:
      strcpy (ptr, "*");
      break;
    default:
      error ("Invalid unary operation specified.");
    }

  argvec[0] = value_struct_elt (&arg1, argvec + 1, tstr, &static_memfuncp, "structure");

  if (argvec[0])
    {
      if (static_memfuncp)
	{
	  argvec[1] = argvec[0];
	  nargs --;
	  argvec++;
	}
      if (noside == EVAL_AVOID_SIDE_EFFECTS)
	{
	  struct type *return_type;
	  return_type
	    = TYPE_TARGET_TYPE (check_typedef (VALUE_TYPE (argvec[0])));
	  return value_zero (return_type, VALUE_LVAL (arg1));
	}
      return call_function_by_hand (argvec[0], nargs, argvec + 1);
    }
  error ("member function %s not found", tstr);
  return 0;			/* For lint -- never reached */
}