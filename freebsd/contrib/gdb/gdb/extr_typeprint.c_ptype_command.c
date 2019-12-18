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
struct expression {int dummy; } ;
struct cleanup {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  do_cleanups (struct cleanup*) ; 
 int /*<<< orphan*/  free_current_contents ; 
 int /*<<< orphan*/  gdb_stdout ; 
 struct cleanup* make_cleanup (int /*<<< orphan*/ ,struct expression**) ; 
 struct expression* parse_expression (char*) ; 
 int /*<<< orphan*/  printf_filtered (char*) ; 
 struct type* ptype_eval (struct expression*) ; 
 int /*<<< orphan*/  type_print (struct type*,char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  whatis_exp (char*,int) ; 

__attribute__((used)) static void
ptype_command (char *typename, int from_tty)
{
  struct type *type;
  struct expression *expr;
  struct cleanup *old_chain;

  if (typename == NULL)
    {
      /* Print type of last thing in value history. */
      whatis_exp (typename, 1);
    }
  else
    {
      expr = parse_expression (typename);
      old_chain = make_cleanup (free_current_contents, &expr);
      type = ptype_eval (expr);
      if (type != NULL)
	{
	  /* User did "ptype <typename>" */
	  printf_filtered ("type = ");
	  type_print (type, "", gdb_stdout, 1);
	  printf_filtered ("\n");
	  do_cleanups (old_chain);
	}
      else
	{
	  /* User did "ptype <symbolname>" */
	  do_cleanups (old_chain);
	  whatis_exp (typename, 1);
	}
    }
}