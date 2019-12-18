#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct value {int dummy; } ;
struct type {int dummy; } ;
struct expression {TYPE_1__* elts; } ;
struct cleanup {int dummy; } ;
struct TYPE_2__ {scalar_t__ opcode; struct type* type; } ;

/* Variables and functions */
 scalar_t__ OP_TYPE ; 
 struct type* VALUE_TYPE (struct value*) ; 
 int /*<<< orphan*/  do_cleanups (struct cleanup*) ; 
 struct value* evaluate_type (struct expression*) ; 
 int /*<<< orphan*/  free_current_contents ; 
 struct cleanup* make_cleanup (int /*<<< orphan*/ ,struct expression**) ; 
 struct expression* parse_expression (char*) ; 
 int /*<<< orphan*/  recursive_dump_type (struct type*,int /*<<< orphan*/ ) ; 

void
maintenance_print_type (char *typename, int from_tty)
{
  struct value *val;
  struct type *type;
  struct cleanup *old_chain;
  struct expression *expr;

  if (typename != NULL)
    {
      expr = parse_expression (typename);
      old_chain = make_cleanup (free_current_contents, &expr);
      if (expr->elts[0].opcode == OP_TYPE)
	{
	  /* The user expression names a type directly, just use that type. */
	  type = expr->elts[1].type;
	}
      else
	{
	  /* The user expression may name a type indirectly by naming an
	     object of that type.  Find that indirectly named type. */
	  val = evaluate_type (expr);
	  type = VALUE_TYPE (val);
	}
      if (type != NULL)
	{
	  recursive_dump_type (type, 0);
	}
      do_cleanups (old_chain);
    }
}