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
struct symbol {int dummy; } ;
struct minimal_symbol {int dummy; } ;
typedef  int /*<<< orphan*/  CORE_ADDR ;

/* Variables and functions */
 scalar_t__ LOC_BLOCK ; 
 scalar_t__ SYMBOL_CLASS (struct symbol*) ; 
 int /*<<< orphan*/  SYMBOL_VALUE_ADDRESS (struct minimal_symbol*) ; 
 int /*<<< orphan*/  VAR_DOMAIN ; 
 struct type* builtin_type_char ; 
 int /*<<< orphan*/  error (char*,...) ; 
 struct type* lookup_function_type (struct type*) ; 
 struct minimal_symbol* lookup_minimal_symbol (char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct type* lookup_pointer_type (struct type*) ; 
 struct symbol* lookup_symbol (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  target_has_execution ; 
 struct value* value_from_pointer (struct type*,int /*<<< orphan*/ ) ; 
 struct value* value_of_variable (struct symbol*,int /*<<< orphan*/ *) ; 

struct value *
find_function_in_inferior (const char *name)
{
  struct symbol *sym;
  sym = lookup_symbol (name, 0, VAR_DOMAIN, 0, NULL);
  if (sym != NULL)
    {
      if (SYMBOL_CLASS (sym) != LOC_BLOCK)
	{
	  error ("\"%s\" exists in this program but is not a function.",
		 name);
	}
      return value_of_variable (sym, NULL);
    }
  else
    {
      struct minimal_symbol *msymbol = lookup_minimal_symbol (name, NULL, NULL);
      if (msymbol != NULL)
	{
	  struct type *type;
	  CORE_ADDR maddr;
	  type = lookup_pointer_type (builtin_type_char);
	  type = lookup_function_type (type);
	  type = lookup_pointer_type (type);
	  maddr = SYMBOL_VALUE_ADDRESS (msymbol);
	  return value_from_pointer (type, maddr);
	}
      else
	{
	  if (!target_has_execution)
	    error ("evaluation of this expression requires the target program to be active");
	  else
	    error ("evaluation of this expression requires the program to have a function \"%s\".", name);
	}
    }
}