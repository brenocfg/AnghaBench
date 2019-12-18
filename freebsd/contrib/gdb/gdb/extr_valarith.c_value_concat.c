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
 int /*<<< orphan*/  COERCE_VARYING_ARRAY (struct value*,struct type*) ; 
 scalar_t__ TYPE_CODE (struct type*) ; 
 scalar_t__ TYPE_CODE_BITSTRING ; 
 scalar_t__ TYPE_CODE_BOOL ; 
 scalar_t__ TYPE_CODE_CHAR ; 
 scalar_t__ TYPE_CODE_INT ; 
 scalar_t__ TYPE_CODE_STRING ; 
 int TYPE_LENGTH (struct type*) ; 
 int /*<<< orphan*/  VALUE_CONTENTS (struct value*) ; 
 int /*<<< orphan*/  VALUE_TYPE (struct value*) ; 
 scalar_t__ alloca (int) ; 
 struct type* check_typedef (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  error (char*) ; 
 int longest_to_int (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (char*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ unpack_long (struct type*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  value_as_long (struct value*) ; 
 struct value* value_string (char*,int) ; 

struct value *
value_concat (struct value *arg1, struct value *arg2)
{
  struct value *inval1;
  struct value *inval2;
  struct value *outval = NULL;
  int inval1len, inval2len;
  int count, idx;
  char *ptr;
  char inchar;
  struct type *type1 = check_typedef (VALUE_TYPE (arg1));
  struct type *type2 = check_typedef (VALUE_TYPE (arg2));

  COERCE_VARYING_ARRAY (arg1, type1);
  COERCE_VARYING_ARRAY (arg2, type2);

  /* First figure out if we are dealing with two values to be concatenated
     or a repeat count and a value to be repeated.  INVAL1 is set to the
     first of two concatenated values, or the repeat count.  INVAL2 is set
     to the second of the two concatenated values or the value to be 
     repeated. */

  if (TYPE_CODE (type2) == TYPE_CODE_INT)
    {
      struct type *tmp = type1;
      type1 = tmp;
      tmp = type2;
      inval1 = arg2;
      inval2 = arg1;
    }
  else
    {
      inval1 = arg1;
      inval2 = arg2;
    }

  /* Now process the input values. */

  if (TYPE_CODE (type1) == TYPE_CODE_INT)
    {
      /* We have a repeat count.  Validate the second value and then
         construct a value repeated that many times. */
      if (TYPE_CODE (type2) == TYPE_CODE_STRING
	  || TYPE_CODE (type2) == TYPE_CODE_CHAR)
	{
	  count = longest_to_int (value_as_long (inval1));
	  inval2len = TYPE_LENGTH (type2);
	  ptr = (char *) alloca (count * inval2len);
	  if (TYPE_CODE (type2) == TYPE_CODE_CHAR)
	    {
	      inchar = (char) unpack_long (type2,
					   VALUE_CONTENTS (inval2));
	      for (idx = 0; idx < count; idx++)
		{
		  *(ptr + idx) = inchar;
		}
	    }
	  else
	    {
	      for (idx = 0; idx < count; idx++)
		{
		  memcpy (ptr + (idx * inval2len), VALUE_CONTENTS (inval2),
			  inval2len);
		}
	    }
	  outval = value_string (ptr, count * inval2len);
	}
      else if (TYPE_CODE (type2) == TYPE_CODE_BITSTRING
	       || TYPE_CODE (type2) == TYPE_CODE_BOOL)
	{
	  error ("unimplemented support for bitstring/boolean repeats");
	}
      else
	{
	  error ("can't repeat values of that type");
	}
    }
  else if (TYPE_CODE (type1) == TYPE_CODE_STRING
	   || TYPE_CODE (type1) == TYPE_CODE_CHAR)
    {
      /* We have two character strings to concatenate. */
      if (TYPE_CODE (type2) != TYPE_CODE_STRING
	  && TYPE_CODE (type2) != TYPE_CODE_CHAR)
	{
	  error ("Strings can only be concatenated with other strings.");
	}
      inval1len = TYPE_LENGTH (type1);
      inval2len = TYPE_LENGTH (type2);
      ptr = (char *) alloca (inval1len + inval2len);
      if (TYPE_CODE (type1) == TYPE_CODE_CHAR)
	{
	  *ptr = (char) unpack_long (type1, VALUE_CONTENTS (inval1));
	}
      else
	{
	  memcpy (ptr, VALUE_CONTENTS (inval1), inval1len);
	}
      if (TYPE_CODE (type2) == TYPE_CODE_CHAR)
	{
	  *(ptr + inval1len) =
	    (char) unpack_long (type2, VALUE_CONTENTS (inval2));
	}
      else
	{
	  memcpy (ptr + inval1len, VALUE_CONTENTS (inval2), inval2len);
	}
      outval = value_string (ptr, inval1len + inval2len);
    }
  else if (TYPE_CODE (type1) == TYPE_CODE_BITSTRING
	   || TYPE_CODE (type1) == TYPE_CODE_BOOL)
    {
      /* We have two bitstrings to concatenate. */
      if (TYPE_CODE (type2) != TYPE_CODE_BITSTRING
	  && TYPE_CODE (type2) != TYPE_CODE_BOOL)
	{
	  error ("Bitstrings or booleans can only be concatenated with other bitstrings or booleans.");
	}
      error ("unimplemented support for bitstring/boolean concatenation.");
    }
  else
    {
      /* We don't know how to concatenate these operands. */
      error ("illegal operands for concatenation.");
    }
  return (outval);
}