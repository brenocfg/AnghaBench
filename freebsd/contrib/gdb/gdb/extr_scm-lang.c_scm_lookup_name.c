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
struct symtab {int dummy; } ;
struct symbol {int dummy; } ;

/* Variables and functions */
 int SCM_EOL ; 
 int /*<<< orphan*/  VAR_DOMAIN ; 
 int /*<<< orphan*/  builtin_type_int ; 
 int /*<<< orphan*/  builtin_type_scm ; 
 struct value* call_function_by_hand (struct value*,int,struct value**) ; 
 int /*<<< orphan*/  error (char*,char*) ; 
 int /*<<< orphan*/ * expression_context_block ; 
 struct value* find_function_in_inferior (char*) ; 
 scalar_t__ in_eval_c () ; 
 struct symbol* lookup_symbol (char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int*,struct symtab**) ; 
 int strlen (char*) ; 
 struct value* value_allocate_space_in_inferior (int) ; 
 int /*<<< orphan*/  value_as_long (struct value*) ; 
 struct value* value_from_longest (int /*<<< orphan*/ ,int) ; 
 struct value* value_ind (struct value*) ; 
 int /*<<< orphan*/  value_logical_not (struct value*) ; 
 struct value* value_of_variable (struct symbol*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_memory (int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static struct value *
scm_lookup_name (char *str)
{
  struct value *args[3];
  int len = strlen (str);
  struct value *func;
  struct value *val;
  struct symbol *sym;
  args[0] = value_allocate_space_in_inferior (len);
  args[1] = value_from_longest (builtin_type_int, len);
  write_memory (value_as_long (args[0]), str, len);

  if (in_eval_c ()
      && (sym = lookup_symbol ("env",
			       expression_context_block,
			       VAR_DOMAIN, (int *) NULL,
			       (struct symtab **) NULL)) != NULL)
    args[2] = value_of_variable (sym, expression_context_block);
  else
    /* FIXME in this case, we should try lookup_symbol first */
    args[2] = value_from_longest (builtin_type_scm, SCM_EOL);

  func = find_function_in_inferior ("scm_lookup_cstr");
  val = call_function_by_hand (func, 3, args);
  if (!value_logical_not (val))
    return value_ind (val);

  sym = lookup_symbol (str,
		       expression_context_block,
		       VAR_DOMAIN, (int *) NULL,
		       (struct symtab **) NULL);
  if (sym)
    return value_of_variable (sym, NULL);
  error ("No symbol \"%s\" in current context.", str);
}