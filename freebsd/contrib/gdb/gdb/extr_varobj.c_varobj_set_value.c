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
struct varobj {int updated; struct value* value; int /*<<< orphan*/  error; } ;
struct value {int dummy; } ;
struct expression {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  gdb_evaluate_expression (struct expression*,struct value**) ; 
 int /*<<< orphan*/  gdb_parse_exp_1 (char**,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct expression**) ; 
 int /*<<< orphan*/  gdb_value_assign (struct value*,struct value*,struct value**) ; 
 int input_radix ; 
 int /*<<< orphan*/  my_value_equal (struct value*,struct value*,int*) ; 
 int /*<<< orphan*/  release_value (struct value*) ; 
 int /*<<< orphan*/  value_free (struct value*) ; 
 scalar_t__ variable_editable (struct varobj*) ; 
 int /*<<< orphan*/  xfree (struct expression*) ; 

int
varobj_set_value (struct varobj *var, char *expression)
{
  struct value *val;
  int error;
  int offset = 0;

  /* The argument "expression" contains the variable's new value.
     We need to first construct a legal expression for this -- ugh! */
  /* Does this cover all the bases? */
  struct expression *exp;
  struct value *value;
  int saved_input_radix = input_radix;

  if (var->value != NULL && variable_editable (var) && !var->error)
    {
      char *s = expression;
      int i;

      input_radix = 10;		/* ALWAYS reset to decimal temporarily */
      if (!gdb_parse_exp_1 (&s, 0, 0, &exp))
	/* We cannot proceed without a well-formed expression. */
	return 0;
      if (!gdb_evaluate_expression (exp, &value))
	{
	  /* We cannot proceed without a valid expression. */
	  xfree (exp);
	  return 0;
	}

      if (!my_value_equal (var->value, value, &error))
        var->updated = 1;
      if (!gdb_value_assign (var->value, value, &val))
	return 0;
      value_free (var->value);
      release_value (val);
      var->value = val;
      input_radix = saved_input_radix;
      return 1;
    }

  return 0;
}