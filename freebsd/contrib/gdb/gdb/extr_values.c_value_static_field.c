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

/* Variables and functions */
 int /*<<< orphan*/  SET_FIELD_PHYSADDR (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SYMBOL_BFD_SECTION (struct minimal_symbol*) ; 
 int /*<<< orphan*/  SYMBOL_VALUE_ADDRESS (struct minimal_symbol*) ; 
 int /*<<< orphan*/  TYPE_FIELD (struct type*,int) ; 
 scalar_t__ TYPE_FIELD_STATIC_HAS_ADDR (struct type*,int) ; 
 int /*<<< orphan*/  TYPE_FIELD_STATIC_PHYSADDR (struct type*,int) ; 
 char* TYPE_FIELD_STATIC_PHYSNAME (struct type*,int) ; 
 int /*<<< orphan*/  TYPE_FIELD_TYPE (struct type*,int) ; 
 int /*<<< orphan*/  VALUE_ADDRESS (struct value*) ; 
 scalar_t__ VALUE_LVAL (struct value*) ; 
 int /*<<< orphan*/  VAR_DOMAIN ; 
 struct minimal_symbol* lookup_minimal_symbol (char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct symbol* lookup_symbol (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ lval_memory ; 
 struct value* read_var_value (struct symbol*,int /*<<< orphan*/ *) ; 
 scalar_t__ symbol_read_needs_frame (struct symbol*) ; 
 struct value* value_at (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  warning (char*) ; 

struct value *
value_static_field (struct type *type, int fieldno)
{
  struct value *retval;

  if (TYPE_FIELD_STATIC_HAS_ADDR (type, fieldno))
    {
      retval = value_at (TYPE_FIELD_TYPE (type, fieldno),
			 TYPE_FIELD_STATIC_PHYSADDR (type, fieldno),
			 NULL);
    }
  else
    {
      char *phys_name = TYPE_FIELD_STATIC_PHYSNAME (type, fieldno);
      struct symbol *sym = lookup_symbol (phys_name, 0, VAR_DOMAIN, 0, NULL);
      if (sym == NULL)
	{
	  /* With some compilers, e.g. HP aCC, static data members are reported
	     as non-debuggable symbols */
	  struct minimal_symbol *msym = lookup_minimal_symbol (phys_name, NULL, NULL);
	  if (!msym)
	    return NULL;
	  else
	    {
	      retval = value_at (TYPE_FIELD_TYPE (type, fieldno),
				 SYMBOL_VALUE_ADDRESS (msym),
				 SYMBOL_BFD_SECTION (msym));
	    }
	}
      else
	{
	  /* SYM should never have a SYMBOL_CLASS which will require
	     read_var_value to use the FRAME parameter.  */
	  if (symbol_read_needs_frame (sym))
	    warning ("static field's value depends on the current "
		     "frame - bad debug info?");
	  retval = read_var_value (sym, NULL);
 	}
      if (retval && VALUE_LVAL (retval) == lval_memory)
	SET_FIELD_PHYSADDR (TYPE_FIELD (type, fieldno),
			    VALUE_ADDRESS (retval));
    }
  return retval;
}