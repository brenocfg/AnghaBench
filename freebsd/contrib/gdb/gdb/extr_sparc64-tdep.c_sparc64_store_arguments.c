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
struct regcache {int dummy; } ;
typedef  int /*<<< orphan*/  buf ;
typedef  int CORE_ADDR ;

/* Variables and functions */
 scalar_t__ BIAS ; 
 int SPARC64_D0_REGNUM ; 
 int SPARC64_D10_REGNUM ; 
 int SPARC64_Q0_REGNUM ; 
 int SPARC64_Q8_REGNUM ; 
 int SPARC_O0_REGNUM ; 
 int TYPE_LENGTH (struct type*) ; 
 char* VALUE_CONTENTS (struct value*) ; 
 struct type* VALUE_TYPE (struct value*) ; 
 int /*<<< orphan*/  builtin_type_int64 ; 
 int /*<<< orphan*/  gdb_assert (int) ; 
 int /*<<< orphan*/  lookup_pointer_type (struct type*) ; 
 char* memcpy (char*,char*,int) ; 
 int /*<<< orphan*/  memset (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  regcache_cooked_write (struct regcache*,int,char*) ; 
 int /*<<< orphan*/  regcache_cooked_write_unsigned (struct regcache*,int,int) ; 
 scalar_t__ sparc64_16_byte_align_p (struct type*) ; 
 scalar_t__ sparc64_floating_p (struct type*) ; 
 int sparc64_integral_or_pointer_p (struct type*) ; 
 int /*<<< orphan*/  sparc64_store_floating_fields (struct regcache*,struct type*,char*,int,int /*<<< orphan*/ ) ; 
 scalar_t__ sparc64_structure_or_union_p (struct type*) ; 
 struct value* value_cast (int /*<<< orphan*/ ,struct value*) ; 
 struct value* value_from_pointer (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  write_memory (int,char*,int) ; 

__attribute__((used)) static CORE_ADDR
sparc64_store_arguments (struct regcache *regcache, int nargs,
			 struct value **args, CORE_ADDR sp,
			 int struct_return, CORE_ADDR struct_addr)
{
  /* Number of extended words in the "parameter array".  */
  int num_elements = 0;
  int element = 0;
  int i;

  /* Take BIAS into account.  */
  sp += BIAS;

  /* First we calculate the number of extended words in the "parameter
     array".  While doing so we also convert some of the arguments.  */

  if (struct_return)
    num_elements++;

  for (i = 0; i < nargs; i++)
    {
      struct type *type = VALUE_TYPE (args[i]);
      int len = TYPE_LENGTH (type);

      if (sparc64_structure_or_union_p (type))
	{
	  /* Structure or Union arguments.  */
	  if (len <= 16)
	    {
	      if (num_elements % 2 && sparc64_16_byte_align_p (type))
		num_elements++;
	      num_elements += ((len + 7) / 8);
	    }
	  else
	    {
	      /* The psABI says that "Structures or unions larger than
		 sixteen bytes are copied by the caller and passed
		 indirectly; the caller will pass the address of a
		 correctly aligned structure value.  This sixty-four
		 bit address will occupy one word in the parameter
		 array, and may be promoted to an %o register like any
		 other pointer value."  Allocate memory for these
		 values on the stack.  */
	      sp -= len;

	      /* Use 16-byte alignment for these values.  That's
                 always correct, and wasting a few bytes shouldn't be
                 a problem.  */
	      sp &= ~0xf;

	      write_memory (sp, VALUE_CONTENTS (args[i]), len);
	      args[i] = value_from_pointer (lookup_pointer_type (type), sp);
	      num_elements++;
	    }
	}
      else if (sparc64_floating_p (type))
	{
	  /* Floating arguments.  */

	  if (len == 16)
	    {
	      /* The psABI says that "Each quad-precision parameter
                 value will be assigned to two extended words in the
                 parameter array.  */
	      num_elements += 2;

	      /* The psABI says that "Long doubles must be
                 quad-aligned, and thus a hole might be introduced
                 into the parameter array to force alignment."  Skip
                 an element if necessary.  */
	      if (num_elements % 2)
		num_elements++;
	    }
	  else
	    num_elements++;
	}
      else
	{
	  /* Integral and pointer arguments.  */
	  gdb_assert (sparc64_integral_or_pointer_p (type));

	  /* The psABI says that "Each argument value of integral type
	     smaller than an extended word will be widened by the
	     caller to an extended word according to the signed-ness
	     of the argument type."  */
	  if (len < 8)
	    args[i] = value_cast (builtin_type_int64, args[i]);
	  num_elements++;
	}
    }

  /* Allocate the "parameter array".  */
  sp -= num_elements * 8;

  /* The psABI says that "Every stack frame must be 16-byte aligned."  */
  sp &= ~0xf;

  /* Now we store the arguments in to the "paramater array".  Some
     Integer or Pointer arguments and Structure or Union arguments
     will be passed in %o registers.  Some Floating arguments and
     floating members of structures are passed in floating-point
     registers.  However, for functions with variable arguments,
     floating arguments are stored in an %0 register, and for
     functions without a prototype floating arguments are stored in
     both a floating-point and an %o registers, or a floating-point
     register and memory.  To simplify the logic here we always pass
     arguments in memory, an %o register, and a floating-point
     register if appropriate.  This should be no problem since the
     contents of any unused memory or registers in the "parameter
     array" are undefined.  */

  if (struct_return)
    {
      regcache_cooked_write_unsigned (regcache, SPARC_O0_REGNUM, struct_addr);
      element++;
    }

  for (i = 0; i < nargs; i++)
    {
      char *valbuf = VALUE_CONTENTS (args[i]);
      struct type *type = VALUE_TYPE (args[i]);
      int len = TYPE_LENGTH (type);
      int regnum = -1;
      char buf[16];

      if (sparc64_structure_or_union_p (type))
	{
	  /* Structure or Union arguments.  */
	  gdb_assert (len <= 16);
	  memset (buf, 0, sizeof (buf));
	  valbuf = memcpy (buf, valbuf, len);

	  if (element % 2 && sparc64_16_byte_align_p (type))
	    element++;

	  if (element < 6)
	    {
	      regnum = SPARC_O0_REGNUM + element;
	      if (len > 8 && element < 5)
		regcache_cooked_write (regcache, regnum + 1, valbuf + 8);
	    }

	  if (element < 16)
	    sparc64_store_floating_fields (regcache, type, valbuf, element, 0);
	}
      else if (sparc64_floating_p (type))
	{
	  /* Floating arguments.  */
	  if (len == 16)
	    {
	      if (element % 2)
		element++;
	      if (element < 16)
		regnum = SPARC64_Q0_REGNUM + element / 2;
	    }
	  else if (len == 8)
	    {
	      if (element < 16)
		regnum = SPARC64_D0_REGNUM + element;
	    }
	  else
	    {
	      /* The psABI says "Each single-precision parameter value
                 will be assigned to one extended word in the
                 parameter array, and right-justified within that
                 word; the left half (even floatregister) is
                 undefined."  Even though the psABI says that "the
                 left half is undefined", set it to zero here.  */
	      memset (buf, 0, 4);
	      memcpy (buf + 4, valbuf, 4);
	      valbuf = buf;
	      len = 8;
	      if (element < 16)
		regnum = SPARC64_D0_REGNUM + element;
	    }
	}
      else
	{
	  /* Integral and pointer arguments.  */
	  gdb_assert (len == 8);
	  if (element < 6)
	    regnum = SPARC_O0_REGNUM + element;
	}

      if (regnum != -1)
	{
	  regcache_cooked_write (regcache, regnum, valbuf);

	  /* If we're storing the value in a floating-point register,
             also store it in the corresponding %0 register(s).  */
	  if (regnum >= SPARC64_D0_REGNUM && regnum <= SPARC64_D10_REGNUM)
	    {
	      gdb_assert (element < 6);
	      regnum = SPARC_O0_REGNUM + element;
	      regcache_cooked_write (regcache, regnum, valbuf);
	    }
	  else if (regnum >= SPARC64_Q0_REGNUM && regnum <= SPARC64_Q8_REGNUM)
	    {
	      gdb_assert (element < 6);
	      regnum = SPARC_O0_REGNUM + element;
	      regcache_cooked_write (regcache, regnum, valbuf);
	      regcache_cooked_write (regcache, regnum + 1, valbuf);
	    }
	}

      /* Always store the argument in memeory.  */
      write_memory (sp + element * 8, valbuf, len);
      element += ((len + 7) / 8);
    }

  gdb_assert (element == num_elements);

  /* Take BIAS into account.  */
  sp -= BIAS;
  return sp;
}