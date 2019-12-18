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
struct fn_field {int dummy; } ;
typedef  int /*<<< orphan*/  VALUE_ADDRESS ;

/* Variables and functions */
 int /*<<< orphan*/  BLOCK_START (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SYMBOL_BLOCK_VALUE (struct symbol*) ; 
 int /*<<< orphan*/  SYMBOL_VALUE_ADDRESS (struct minimal_symbol*) ; 
 char* TYPE_FN_FIELD_PHYSNAME (struct fn_field*,int) ; 
 struct type* TYPE_FN_FIELD_TYPE (struct fn_field*,int) ; 
 struct type* VALUE_TYPE (struct value*) ; 
 int /*<<< orphan*/  VAR_DOMAIN ; 
 struct value* allocate_value (struct type*) ; 
 int /*<<< orphan*/  gdb_assert (int /*<<< orphan*/ ) ; 
 struct minimal_symbol* lookup_minimal_symbol (char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lookup_pointer_type (struct type*) ; 
 struct symbol* lookup_symbol (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  value_addr (struct value*) ; 
 int /*<<< orphan*/  value_cast (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct value* value_ind (int /*<<< orphan*/ ) ; 

struct value *
value_fn_field (struct value **arg1p, struct fn_field *f, int j, struct type *type,
		int offset)
{
  struct value *v;
  struct type *ftype = TYPE_FN_FIELD_TYPE (f, j);
  char *physname = TYPE_FN_FIELD_PHYSNAME (f, j);
  struct symbol *sym;
  struct minimal_symbol *msym;

  sym = lookup_symbol (physname, 0, VAR_DOMAIN, 0, NULL);
  if (sym != NULL)
    {
      msym = NULL;
    }
  else
    {
      gdb_assert (sym == NULL);
      msym = lookup_minimal_symbol (physname, NULL, NULL);
      if (msym == NULL)
	return NULL;
    }

  v = allocate_value (ftype);
  if (sym)
    {
      VALUE_ADDRESS (v) = BLOCK_START (SYMBOL_BLOCK_VALUE (sym));
    }
  else
    {
      VALUE_ADDRESS (v) = SYMBOL_VALUE_ADDRESS (msym);
    }

  if (arg1p)
    {
      if (type != VALUE_TYPE (*arg1p))
	*arg1p = value_ind (value_cast (lookup_pointer_type (type),
					value_addr (*arg1p)));

      /* Move the `this' pointer according to the offset.
         VALUE_OFFSET (*arg1p) += offset;
       */
    }

  return v;
}