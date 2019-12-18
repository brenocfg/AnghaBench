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
struct type {int dummy; } ;
typedef  enum type_code { ____Placeholder_type_code } type_code ;
typedef  double ULONGEST ;
typedef  double DOUBLEST ;

/* Variables and functions */
 int /*<<< orphan*/  CHECK_TYPEDEF (struct type*) ; 
 int TYPE_CODE (struct type*) ; 
 int TYPE_CODE_FLT ; 
 int TYPE_LENGTH (struct type*) ; 
 int TYPE_UNSIGNED (struct type*) ; 
 double extract_typed_floating (char const*,struct type*) ; 
 int /*<<< orphan*/  floatformat_from_type (struct type*) ; 
 int /*<<< orphan*/  floatformat_is_valid (int /*<<< orphan*/ ,char const*) ; 
 double unpack_long (struct type*,char const*) ; 

DOUBLEST
unpack_double (struct type *type, const char *valaddr, int *invp)
{
  enum type_code code;
  int len;
  int nosign;

  *invp = 0;			/* Assume valid.   */
  CHECK_TYPEDEF (type);
  code = TYPE_CODE (type);
  len = TYPE_LENGTH (type);
  nosign = TYPE_UNSIGNED (type);
  if (code == TYPE_CODE_FLT)
    {
      /* NOTE: cagney/2002-02-19: There was a test here to see if the
	 floating-point value was valid (using the macro
	 INVALID_FLOAT).  That test/macro have been removed.

	 It turns out that only the VAX defined this macro and then
	 only in a non-portable way.  Fixing the portability problem
	 wouldn't help since the VAX floating-point code is also badly
	 bit-rotten.  The target needs to add definitions for the
	 methods TARGET_FLOAT_FORMAT and TARGET_DOUBLE_FORMAT - these
	 exactly describe the target floating-point format.  The
	 problem here is that the corresponding floatformat_vax_f and
	 floatformat_vax_d values these methods should be set to are
	 also not defined either.  Oops!

         Hopefully someone will add both the missing floatformat
         definitions and the new cases for floatformat_is_valid ().  */

      if (!floatformat_is_valid (floatformat_from_type (type), valaddr))
	{
	  *invp = 1;
	  return 0.0;
	}

      return extract_typed_floating (valaddr, type);
    }
  else if (nosign)
    {
      /* Unsigned -- be sure we compensate for signed LONGEST.  */
      return (ULONGEST) unpack_long (type, valaddr);
    }
  else
    {
      /* Signed -- we are OK with unpack_long.  */
      return unpack_long (type, valaddr);
    }
}