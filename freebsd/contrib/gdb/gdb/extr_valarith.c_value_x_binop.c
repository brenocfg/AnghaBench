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
#define  BINOP_ADD 151 
#define  BINOP_ASSIGN 150 
#define  BINOP_ASSIGN_MODIFY 149 
#define  BINOP_BITWISE_AND 148 
#define  BINOP_BITWISE_IOR 147 
#define  BINOP_BITWISE_XOR 146 
#define  BINOP_DIV 145 
#define  BINOP_EQUAL 144 
#define  BINOP_GEQ 143 
#define  BINOP_GTR 142 
#define  BINOP_LEQ 141 
#define  BINOP_LESS 140 
#define  BINOP_LOGICAL_AND 139 
#define  BINOP_LOGICAL_OR 138 
#define  BINOP_LSH 137 
#define  BINOP_MAX 136 
#define  BINOP_MIN 135 
#define  BINOP_MOD 134 
#define  BINOP_MUL 133 
#define  BINOP_NOTEQUAL 132 
#define  BINOP_REM 131 
#define  BINOP_RSH 130 
#define  BINOP_SUB 129 
#define  BINOP_SUBSCRIPT 128 
 int /*<<< orphan*/  COERCE_ENUM (struct value*) ; 
 int /*<<< orphan*/  COERCE_REF (struct value*) ; 
 int EVAL_AVOID_SIDE_EFFECTS ; 
 scalar_t__ TYPE_CODE (int /*<<< orphan*/ ) ; 
 scalar_t__ TYPE_CODE_STRUCT ; 
 struct type* TYPE_TARGET_TYPE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VALUE_LVAL (struct value*) ; 
 int /*<<< orphan*/  VALUE_TYPE (struct value*) ; 
 scalar_t__ alloca (int) ; 
 struct value* call_function_by_hand (struct value*,int,struct value**) ; 
 int /*<<< orphan*/  check_typedef (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  error (char*,...) ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 
 struct value* value_addr (struct value*) ; 
 struct value* value_struct_elt (struct value**,struct value**,char*,int*,char*) ; 
 struct value* value_zero (struct type*,int /*<<< orphan*/ ) ; 

struct value *
value_x_binop (struct value *arg1, struct value *arg2, enum exp_opcode op,
	       enum exp_opcode otherop, enum noside noside)
{
  struct value **argvec;
  char *ptr;
  char tstr[13];
  int static_memfuncp;

  COERCE_REF (arg1);
  COERCE_REF (arg2);
  COERCE_ENUM (arg1);
  COERCE_ENUM (arg2);

  /* now we know that what we have to do is construct our
     arg vector and find the right function to call it with.  */

  if (TYPE_CODE (check_typedef (VALUE_TYPE (arg1))) != TYPE_CODE_STRUCT)
    error ("Can't do that binary op on that type");	/* FIXME be explicit */

  argvec = (struct value **) alloca (sizeof (struct value *) * 4);
  argvec[1] = value_addr (arg1);
  argvec[2] = arg2;
  argvec[3] = 0;

  /* make the right function name up */
  strcpy (tstr, "operator__");
  ptr = tstr + 8;
  switch (op)
    {
    case BINOP_ADD:
      strcpy (ptr, "+");
      break;
    case BINOP_SUB:
      strcpy (ptr, "-");
      break;
    case BINOP_MUL:
      strcpy (ptr, "*");
      break;
    case BINOP_DIV:
      strcpy (ptr, "/");
      break;
    case BINOP_REM:
      strcpy (ptr, "%");
      break;
    case BINOP_LSH:
      strcpy (ptr, "<<");
      break;
    case BINOP_RSH:
      strcpy (ptr, ">>");
      break;
    case BINOP_BITWISE_AND:
      strcpy (ptr, "&");
      break;
    case BINOP_BITWISE_IOR:
      strcpy (ptr, "|");
      break;
    case BINOP_BITWISE_XOR:
      strcpy (ptr, "^");
      break;
    case BINOP_LOGICAL_AND:
      strcpy (ptr, "&&");
      break;
    case BINOP_LOGICAL_OR:
      strcpy (ptr, "||");
      break;
    case BINOP_MIN:
      strcpy (ptr, "<?");
      break;
    case BINOP_MAX:
      strcpy (ptr, ">?");
      break;
    case BINOP_ASSIGN:
      strcpy (ptr, "=");
      break;
    case BINOP_ASSIGN_MODIFY:
      switch (otherop)
	{
	case BINOP_ADD:
	  strcpy (ptr, "+=");
	  break;
	case BINOP_SUB:
	  strcpy (ptr, "-=");
	  break;
	case BINOP_MUL:
	  strcpy (ptr, "*=");
	  break;
	case BINOP_DIV:
	  strcpy (ptr, "/=");
	  break;
	case BINOP_REM:
	  strcpy (ptr, "%=");
	  break;
	case BINOP_BITWISE_AND:
	  strcpy (ptr, "&=");
	  break;
	case BINOP_BITWISE_IOR:
	  strcpy (ptr, "|=");
	  break;
	case BINOP_BITWISE_XOR:
	  strcpy (ptr, "^=");
	  break;
	case BINOP_MOD:	/* invalid */
	default:
	  error ("Invalid binary operation specified.");
	}
      break;
    case BINOP_SUBSCRIPT:
      strcpy (ptr, "[]");
      break;
    case BINOP_EQUAL:
      strcpy (ptr, "==");
      break;
    case BINOP_NOTEQUAL:
      strcpy (ptr, "!=");
      break;
    case BINOP_LESS:
      strcpy (ptr, "<");
      break;
    case BINOP_GTR:
      strcpy (ptr, ">");
      break;
    case BINOP_GEQ:
      strcpy (ptr, ">=");
      break;
    case BINOP_LEQ:
      strcpy (ptr, "<=");
      break;
    case BINOP_MOD:		/* invalid */
    default:
      error ("Invalid binary operation specified.");
    }

  argvec[0] = value_struct_elt (&arg1, argvec + 1, tstr, &static_memfuncp, "structure");

  if (argvec[0])
    {
      if (static_memfuncp)
	{
	  argvec[1] = argvec[0];
	  argvec++;
	}
      if (noside == EVAL_AVOID_SIDE_EFFECTS)
	{
	  struct type *return_type;
	  return_type
	    = TYPE_TARGET_TYPE (check_typedef (VALUE_TYPE (argvec[0])));
	  return value_zero (return_type, VALUE_LVAL (arg1));
	}
      return call_function_by_hand (argvec[0], 2 - static_memfuncp, argvec + 1);
    }
  error ("member function %s not found", tstr);
#ifdef lint
  return call_function_by_hand (argvec[0], 2 - static_memfuncp, argvec + 1);
#endif
}