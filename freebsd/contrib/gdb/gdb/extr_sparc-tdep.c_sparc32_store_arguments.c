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
typedef  int CORE_ADDR ;

/* Variables and functions */
 int SPARC_O0_REGNUM ; 
 int TYPE_LENGTH (struct type*) ; 
 char* VALUE_CONTENTS (struct value*) ; 
 struct type* VALUE_TYPE (struct value*) ; 
 int /*<<< orphan*/  builtin_type_int32 ; 
 int /*<<< orphan*/  gdb_assert (int) ; 
 int /*<<< orphan*/  lookup_pointer_type (struct type*) ; 
 int max (int,int) ; 
 int /*<<< orphan*/  regcache_cooked_write (struct regcache*,int,char*) ; 
 scalar_t__ sparc_floating_p (struct type*) ; 
 int sparc_integral_or_pointer_p (struct type*) ; 
 scalar_t__ sparc_structure_or_union_p (struct type*) ; 
 int /*<<< orphan*/  store_unsigned_integer (char*,int,int) ; 
 struct value* value_cast (int /*<<< orphan*/ ,struct value*) ; 
 struct value* value_from_pointer (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  write_memory (int,char*,int) ; 

__attribute__((used)) static CORE_ADDR
sparc32_store_arguments (struct regcache *regcache, int nargs,
			 struct value **args, CORE_ADDR sp,
			 int struct_return, CORE_ADDR struct_addr)
{
  /* Number of words in the "parameter array".  */
  int num_elements = 0;
  int element = 0;
  int i;

  for (i = 0; i < nargs; i++)
    {
      struct type *type = VALUE_TYPE (args[i]);
      int len = TYPE_LENGTH (type);

      if (sparc_structure_or_union_p (type)
	  || (sparc_floating_p (type) && len == 16))
	{
	  /* Structure, Union and Quad-Precision Arguments.  */
	  sp -= len;

	  /* Use doubleword alignment for these values.  That's always
             correct, and wasting a few bytes shouldn't be a problem.  */
	  sp &= ~0x7;

	  write_memory (sp, VALUE_CONTENTS (args[i]), len);
	  args[i] = value_from_pointer (lookup_pointer_type (type), sp);
	  num_elements++;
	}
      else if (sparc_floating_p (type))
	{
	  /* Floating arguments.  */
	  gdb_assert (len == 4 || len == 8);
	  num_elements += (len / 4);
	}
      else
	{
	  /* Integral and pointer arguments.  */
	  gdb_assert (sparc_integral_or_pointer_p (type));

	  if (len < 4)
	    args[i] = value_cast (builtin_type_int32, args[i]);
	  num_elements += ((len + 3) / 4);
	}
    }

  /* Always allocate at least six words.  */
  sp -= max (6, num_elements) * 4;

  /* The psABI says that "Software convention requires space for the
     struct/union return value pointer, even if the word is unused."  */
  sp -= 4;

  /* The psABI says that "Although software convention and the
     operating system require every stack frame to be doubleword
     aligned."  */
  sp &= ~0x7;

  for (i = 0; i < nargs; i++)
    {
      char *valbuf = VALUE_CONTENTS (args[i]);
      struct type *type = VALUE_TYPE (args[i]);
      int len = TYPE_LENGTH (type);

      gdb_assert (len == 4 || len == 8);

      if (element < 6)
	{
	  int regnum = SPARC_O0_REGNUM + element;

	  regcache_cooked_write (regcache, regnum, valbuf);
	  if (len > 4 && element < 5)
	    regcache_cooked_write (regcache, regnum + 1, valbuf + 4);
	}

      /* Always store the argument in memory.  */
      write_memory (sp + 4 + element * 4, valbuf, len);
      element += len / 4;
    }

  gdb_assert (element == num_elements);

  if (struct_return)
    {
      char buf[4];

      store_unsigned_integer (buf, 4, struct_addr);
      write_memory (sp, buf, 4);
    }

  return sp;
}