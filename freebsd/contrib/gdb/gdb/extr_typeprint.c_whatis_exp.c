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
struct expression {int dummy; } ;
struct cleanup {int dummy; } ;

/* Variables and functions */
 scalar_t__ TYPE_CODE (struct type*) ; 
 scalar_t__ TYPE_CODE_CLASS ; 
 scalar_t__ TYPE_CODE_PTR ; 
 scalar_t__ TYPE_CODE_REF ; 
 struct type* TYPE_TARGET_TYPE (struct type*) ; 
 struct type* VALUE_TYPE (struct value*) ; 
 struct value* access_value_history (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  do_cleanups (struct cleanup*) ; 
 struct value* evaluate_type (struct expression*) ; 
 int /*<<< orphan*/  free_current_contents ; 
 int /*<<< orphan*/  gdb_stdout ; 
 struct type* lookup_pointer_type (struct type*) ; 
 struct type* lookup_reference_type (struct type*) ; 
 struct cleanup* make_cleanup (int /*<<< orphan*/ ,struct expression**) ; 
 scalar_t__ objectprint ; 
 struct expression* parse_expression (char*) ; 
 int /*<<< orphan*/  printf_filtered (char*) ; 
 int /*<<< orphan*/  type_print (struct type*,char*,int /*<<< orphan*/ ,int) ; 
 struct type* value_rtti_target_type (struct value*,int*,int*,int*) ; 
 struct type* value_rtti_type (struct value*,int*,int*,int*) ; 

__attribute__((used)) static void
whatis_exp (char *exp, int show)
{
  struct expression *expr;
  struct value *val;
  struct cleanup *old_chain = NULL;
  struct type *real_type = NULL;
  struct type *type;
  int full = 0;
  int top = -1;
  int using_enc = 0;

  if (exp)
    {
      expr = parse_expression (exp);
      old_chain = make_cleanup (free_current_contents, &expr);
      val = evaluate_type (expr);
    }
  else
    val = access_value_history (0);

  type = VALUE_TYPE (val);

  if (objectprint)
    {
      if (((TYPE_CODE (type) == TYPE_CODE_PTR) ||
           (TYPE_CODE (type) == TYPE_CODE_REF))
          &&
          (TYPE_CODE (TYPE_TARGET_TYPE (type)) == TYPE_CODE_CLASS))
        {
          real_type = value_rtti_target_type (val, &full, &top, &using_enc);
          if (real_type)
            {
              if (TYPE_CODE (type) == TYPE_CODE_PTR)
                real_type = lookup_pointer_type (real_type);
              else
                real_type = lookup_reference_type (real_type);
            }
        }
      else if (TYPE_CODE (type) == TYPE_CODE_CLASS)
  real_type = value_rtti_type (val, &full, &top, &using_enc);
    }

  printf_filtered ("type = ");

  if (real_type)
    {
      printf_filtered ("/* real type = ");
      type_print (real_type, "", gdb_stdout, -1);
      if (! full)
        printf_filtered (" (incomplete object)");
      printf_filtered (" */\n");    
    }

  type_print (type, "", gdb_stdout, show);
  printf_filtered ("\n");

  if (exp)
    do_cleanups (old_chain);
}