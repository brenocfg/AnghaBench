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
typedef  enum exp_opcode { ____Placeholder_exp_opcode } exp_opcode ;
typedef  unsigned int ULONGEST ;
typedef  unsigned int LONGEST ;
typedef  unsigned int DOUBLEST ;

/* Variables and functions */
#define  BINOP_ADD 146 
#define  BINOP_BITWISE_AND 145 
#define  BINOP_BITWISE_IOR 144 
#define  BINOP_BITWISE_XOR 143 
#define  BINOP_DIV 142 
#define  BINOP_EQUAL 141 
#define  BINOP_EXP 140 
#define  BINOP_LESS 139 
#define  BINOP_LOGICAL_AND 138 
#define  BINOP_LOGICAL_OR 137 
#define  BINOP_LSH 136 
#define  BINOP_MAX 135 
#define  BINOP_MIN 134 
#define  BINOP_MOD 133 
#define  BINOP_MUL 132 
#define  BINOP_NOTEQUAL 131 
#define  BINOP_REM 130 
#define  BINOP_RSH 129 
#define  BINOP_SUB 128 
 int /*<<< orphan*/  COERCE_ENUM (struct value*) ; 
 int /*<<< orphan*/  COERCE_REF (struct value*) ; 
 unsigned int HOST_CHAR_BIT ; 
 int TARGET_DOUBLE_BIT ; 
 unsigned int TARGET_LONG_BIT ; 
 int /*<<< orphan*/  TRUNCATION_TOWARDS_ZERO ; 
 scalar_t__ TYPE_CODE (struct type*) ; 
 scalar_t__ TYPE_CODE_BOOL ; 
 scalar_t__ TYPE_CODE_CHAR ; 
 scalar_t__ TYPE_CODE_FLT ; 
 scalar_t__ TYPE_CODE_INT ; 
 scalar_t__ TYPE_CODE_RANGE ; 
 unsigned int TYPE_LENGTH (struct type*) ; 
 int TYPE_UNSIGNED (struct type*) ; 
 int /*<<< orphan*/  VALUE_CONTENTS_RAW (struct value*) ; 
 struct type* VALUE_TYPE (struct value*) ; 
 struct value* allocate_value (struct type*) ; 
 struct type* builtin_type_double ; 
 struct type* builtin_type_int ; 
 struct type* builtin_type_long ; 
 struct type* builtin_type_long_double ; 
 struct type* builtin_type_long_long ; 
 struct type* builtin_type_unsigned_long ; 
 struct type* builtin_type_unsigned_long_long ; 
 struct type* check_typedef (struct type*) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  error (char*,...) ; 
 unsigned int pow (unsigned int,unsigned int) ; 
 int /*<<< orphan*/  safe_strerror (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  store_signed_integer (int /*<<< orphan*/ ,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  store_typed_floating (int /*<<< orphan*/ ,struct type*,unsigned int) ; 
 int /*<<< orphan*/  store_unsigned_integer (int /*<<< orphan*/ ,unsigned int,unsigned int) ; 
 unsigned int value_as_double (struct value*) ; 
 unsigned int value_as_long (struct value*) ; 

struct value *
value_binop (struct value *arg1, struct value *arg2, enum exp_opcode op)
{
  struct value *val;
  struct type *type1, *type2;

  COERCE_REF (arg1);
  COERCE_REF (arg2);
  COERCE_ENUM (arg1);
  COERCE_ENUM (arg2);
  type1 = check_typedef (VALUE_TYPE (arg1));
  type2 = check_typedef (VALUE_TYPE (arg2));

  if ((TYPE_CODE (type1) != TYPE_CODE_FLT
       && TYPE_CODE (type1) != TYPE_CODE_CHAR
       && TYPE_CODE (type1) != TYPE_CODE_INT
       && TYPE_CODE (type1) != TYPE_CODE_BOOL
       && TYPE_CODE (type1) != TYPE_CODE_RANGE)
      ||
      (TYPE_CODE (type2) != TYPE_CODE_FLT
       && TYPE_CODE (type2) != TYPE_CODE_CHAR
       && TYPE_CODE (type2) != TYPE_CODE_INT
       && TYPE_CODE (type2) != TYPE_CODE_BOOL
       && TYPE_CODE (type2) != TYPE_CODE_RANGE))
    error ("Argument to arithmetic operation not a number or boolean.");

  if (TYPE_CODE (type1) == TYPE_CODE_FLT
      ||
      TYPE_CODE (type2) == TYPE_CODE_FLT)
    {
      /* FIXME-if-picky-about-floating-accuracy: Should be doing this
         in target format.  real.c in GCC probably has the necessary
         code.  */
      DOUBLEST v1, v2, v = 0;
      v1 = value_as_double (arg1);
      v2 = value_as_double (arg2);
      switch (op)
	{
	case BINOP_ADD:
	  v = v1 + v2;
	  break;

	case BINOP_SUB:
	  v = v1 - v2;
	  break;

	case BINOP_MUL:
	  v = v1 * v2;
	  break;

	case BINOP_DIV:
	  v = v1 / v2;
	  break;

        case BINOP_EXP:
          v = pow (v1, v2);
          if (errno)
            error ("Cannot perform exponentiation: %s", safe_strerror (errno));
          break;

	default:
	  error ("Integer-only operation on floating point number.");
	}

      /* If either arg was long double, make sure that value is also long
         double.  */

      if (TYPE_LENGTH (type1) * 8 > TARGET_DOUBLE_BIT
	  || TYPE_LENGTH (type2) * 8 > TARGET_DOUBLE_BIT)
	val = allocate_value (builtin_type_long_double);
      else
	val = allocate_value (builtin_type_double);

      store_typed_floating (VALUE_CONTENTS_RAW (val), VALUE_TYPE (val), v);
    }
  else if (TYPE_CODE (type1) == TYPE_CODE_BOOL
	   &&
	   TYPE_CODE (type2) == TYPE_CODE_BOOL)
    {
      LONGEST v1, v2, v = 0;
      v1 = value_as_long (arg1);
      v2 = value_as_long (arg2);

      switch (op)
	{
	case BINOP_BITWISE_AND:
	  v = v1 & v2;
	  break;

	case BINOP_BITWISE_IOR:
	  v = v1 | v2;
	  break;

	case BINOP_BITWISE_XOR:
	  v = v1 ^ v2;
          break;
              
        case BINOP_EQUAL:
          v = v1 == v2;
          break;
          
        case BINOP_NOTEQUAL:
          v = v1 != v2;
	  break;

	default:
	  error ("Invalid operation on booleans.");
	}

      val = allocate_value (type1);
      store_signed_integer (VALUE_CONTENTS_RAW (val),
			    TYPE_LENGTH (type1),
			    v);
    }
  else
    /* Integral operations here.  */
    /* FIXME:  Also mixed integral/booleans, with result an integer. */
    /* FIXME: This implements ANSI C rules (also correct for C++).
       What about FORTRAN and (the deleted) chill ?  */
    {
      unsigned int promoted_len1 = TYPE_LENGTH (type1);
      unsigned int promoted_len2 = TYPE_LENGTH (type2);
      int is_unsigned1 = TYPE_UNSIGNED (type1);
      int is_unsigned2 = TYPE_UNSIGNED (type2);
      unsigned int result_len;
      int unsigned_operation;

      /* Determine type length and signedness after promotion for
         both operands.  */
      if (promoted_len1 < TYPE_LENGTH (builtin_type_int))
	{
	  is_unsigned1 = 0;
	  promoted_len1 = TYPE_LENGTH (builtin_type_int);
	}
      if (promoted_len2 < TYPE_LENGTH (builtin_type_int))
	{
	  is_unsigned2 = 0;
	  promoted_len2 = TYPE_LENGTH (builtin_type_int);
	}

      /* Determine type length of the result, and if the operation should
         be done unsigned.
         Use the signedness of the operand with the greater length.
         If both operands are of equal length, use unsigned operation
         if one of the operands is unsigned.  */
      if (promoted_len1 > promoted_len2)
	{
	  unsigned_operation = is_unsigned1;
	  result_len = promoted_len1;
	}
      else if (promoted_len2 > promoted_len1)
	{
	  unsigned_operation = is_unsigned2;
	  result_len = promoted_len2;
	}
      else
	{
	  unsigned_operation = is_unsigned1 || is_unsigned2;
	  result_len = promoted_len1;
	}

      if (unsigned_operation)
	{
	  ULONGEST v1, v2, v = 0;
	  v1 = (ULONGEST) value_as_long (arg1);
	  v2 = (ULONGEST) value_as_long (arg2);

	  /* Truncate values to the type length of the result.  */
	  if (result_len < sizeof (ULONGEST))
	    {
	      v1 &= ((LONGEST) 1 << HOST_CHAR_BIT * result_len) - 1;
	      v2 &= ((LONGEST) 1 << HOST_CHAR_BIT * result_len) - 1;
	    }

	  switch (op)
	    {
	    case BINOP_ADD:
	      v = v1 + v2;
	      break;

	    case BINOP_SUB:
	      v = v1 - v2;
	      break;

	    case BINOP_MUL:
	      v = v1 * v2;
	      break;

	    case BINOP_DIV:
	      v = v1 / v2;
	      break;

            case BINOP_EXP:
              v = pow (v1, v2);
              if (errno)
                error ("Cannot perform exponentiation: %s", safe_strerror (errno));
              break;

	    case BINOP_REM:
	      v = v1 % v2;
	      break;

	    case BINOP_MOD:
	      /* Knuth 1.2.4, integer only.  Note that unlike the C '%' op,
	         v1 mod 0 has a defined value, v1. */
	      if (v2 == 0)
		{
		  v = v1;
		}
	      else
		{
		  v = v1 / v2;
		  /* Note floor(v1/v2) == v1/v2 for unsigned. */
		  v = v1 - (v2 * v);
		}
	      break;

	    case BINOP_LSH:
	      v = v1 << v2;
	      break;

	    case BINOP_RSH:
	      v = v1 >> v2;
	      break;

	    case BINOP_BITWISE_AND:
	      v = v1 & v2;
	      break;

	    case BINOP_BITWISE_IOR:
	      v = v1 | v2;
	      break;

	    case BINOP_BITWISE_XOR:
	      v = v1 ^ v2;
	      break;

	    case BINOP_LOGICAL_AND:
	      v = v1 && v2;
	      break;

	    case BINOP_LOGICAL_OR:
	      v = v1 || v2;
	      break;

	    case BINOP_MIN:
	      v = v1 < v2 ? v1 : v2;
	      break;

	    case BINOP_MAX:
	      v = v1 > v2 ? v1 : v2;
	      break;

	    case BINOP_EQUAL:
	      v = v1 == v2;
	      break;

            case BINOP_NOTEQUAL:
              v = v1 != v2;
              break;

	    case BINOP_LESS:
	      v = v1 < v2;
	      break;

	    default:
	      error ("Invalid binary operation on numbers.");
	    }

	  /* This is a kludge to get around the fact that we don't
	     know how to determine the result type from the types of
	     the operands.  (I'm not really sure how much we feel the
	     need to duplicate the exact rules of the current
	     language.  They can get really hairy.  But not to do so
	     makes it hard to document just what we *do* do).  */

	  /* Can't just call init_type because we wouldn't know what
	     name to give the type.  */
	  val = allocate_value
	    (result_len > TARGET_LONG_BIT / HOST_CHAR_BIT
	     ? builtin_type_unsigned_long_long
	     : builtin_type_unsigned_long);
	  store_unsigned_integer (VALUE_CONTENTS_RAW (val),
				  TYPE_LENGTH (VALUE_TYPE (val)),
				  v);
	}
      else
	{
	  LONGEST v1, v2, v = 0;
	  v1 = value_as_long (arg1);
	  v2 = value_as_long (arg2);

	  switch (op)
	    {
	    case BINOP_ADD:
	      v = v1 + v2;
	      break;

	    case BINOP_SUB:
	      v = v1 - v2;
	      break;

	    case BINOP_MUL:
	      v = v1 * v2;
	      break;

	    case BINOP_DIV:
	      v = v1 / v2;
              break;

            case BINOP_EXP:
              v = pow (v1, v2);
              if (errno)
                error ("Cannot perform exponentiation: %s", safe_strerror (errno));
	      break;

	    case BINOP_REM:
	      v = v1 % v2;
	      break;

	    case BINOP_MOD:
	      /* Knuth 1.2.4, integer only.  Note that unlike the C '%' op,
	         X mod 0 has a defined value, X. */
	      if (v2 == 0)
		{
		  v = v1;
		}
	      else
		{
		  v = v1 / v2;
		  /* Compute floor. */
		  if (TRUNCATION_TOWARDS_ZERO && (v < 0) && ((v1 % v2) != 0))
		    {
		      v--;
		    }
		  v = v1 - (v2 * v);
		}
	      break;

	    case BINOP_LSH:
	      v = v1 << v2;
	      break;

	    case BINOP_RSH:
	      v = v1 >> v2;
	      break;

	    case BINOP_BITWISE_AND:
	      v = v1 & v2;
	      break;

	    case BINOP_BITWISE_IOR:
	      v = v1 | v2;
	      break;

	    case BINOP_BITWISE_XOR:
	      v = v1 ^ v2;
	      break;

	    case BINOP_LOGICAL_AND:
	      v = v1 && v2;
	      break;

	    case BINOP_LOGICAL_OR:
	      v = v1 || v2;
	      break;

	    case BINOP_MIN:
	      v = v1 < v2 ? v1 : v2;
	      break;

	    case BINOP_MAX:
	      v = v1 > v2 ? v1 : v2;
	      break;

	    case BINOP_EQUAL:
	      v = v1 == v2;
	      break;

	    case BINOP_LESS:
	      v = v1 < v2;
	      break;

	    default:
	      error ("Invalid binary operation on numbers.");
	    }

	  /* This is a kludge to get around the fact that we don't
	     know how to determine the result type from the types of
	     the operands.  (I'm not really sure how much we feel the
	     need to duplicate the exact rules of the current
	     language.  They can get really hairy.  But not to do so
	     makes it hard to document just what we *do* do).  */

	  /* Can't just call init_type because we wouldn't know what
	     name to give the type.  */
	  val = allocate_value
	    (result_len > TARGET_LONG_BIT / HOST_CHAR_BIT
	     ? builtin_type_long_long
	     : builtin_type_long);
	  store_signed_integer (VALUE_CONTENTS_RAW (val),
				TYPE_LENGTH (VALUE_TYPE (val)),
				v);
	}
    }

  return val;
}