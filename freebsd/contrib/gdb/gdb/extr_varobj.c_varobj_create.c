#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct varobj {void* obj_name; TYPE_2__* root; int /*<<< orphan*/  value; int /*<<< orphan*/  type; void* name; int /*<<< orphan*/  format; } ;
struct frame_info {int dummy; } ;
struct cleanup {int dummy; } ;
struct block {int dummy; } ;
typedef  enum varobj_type { ____Placeholder_varobj_type } varobj_type ;
typedef  enum varobj_languages { ____Placeholder_varobj_languages } varobj_languages ;
struct TYPE_8__ {TYPE_1__* elts; } ;
struct TYPE_7__ {int use_selected_frame; struct varobj* rootvar; int /*<<< orphan*/  lang; TYPE_3__* exp; int /*<<< orphan*/  frame; int /*<<< orphan*/ * valid_block; } ;
struct TYPE_6__ {scalar_t__ opcode; } ;
typedef  int /*<<< orphan*/  CORE_ADDR ;

/* Variables and functions */
 scalar_t__ OP_TYPE ; 
 int USE_CURRENT_FRAME ; 
 int USE_SELECTED_FRAME ; 
 scalar_t__ VALUE_LAZY (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VALUE_TYPE (int /*<<< orphan*/ ) ; 
 struct frame_info* deprecated_selected_frame ; 
 int /*<<< orphan*/  discard_cleanups (struct cleanup*) ; 
 int /*<<< orphan*/  do_cleanups (struct cleanup*) ; 
 int /*<<< orphan*/  evaluate_type (TYPE_3__*) ; 
 struct frame_info* find_frame_addr_in_frame_chain (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fprintf_unfiltered (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ gdb_evaluate_expression (TYPE_3__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gdb_parse_exp_1 (char**,struct block*,int /*<<< orphan*/ ,TYPE_3__**) ; 
 int /*<<< orphan*/  gdb_stderr ; 
 int /*<<< orphan*/  gdb_value_fetch_lazy (int /*<<< orphan*/ ) ; 
 struct block* get_frame_block (struct frame_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_frame_id (struct frame_info*) ; 
 int /*<<< orphan*/ * innermost_block ; 
 int /*<<< orphan*/  install_variable (struct varobj*) ; 
 int /*<<< orphan*/ * languages ; 
 struct cleanup* make_cleanup_free_variable (struct varobj*) ; 
 struct varobj* new_root_variable () ; 
 int /*<<< orphan*/  release_value (int /*<<< orphan*/ ) ; 
 void* savestring (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  select_frame (struct frame_info*) ; 
 int /*<<< orphan*/  strlen (char*) ; 
 int /*<<< orphan*/  variable_default_display (struct varobj*) ; 
 int variable_language (struct varobj*) ; 

struct varobj *
varobj_create (char *objname,
	       char *expression, CORE_ADDR frame, enum varobj_type type)
{
  struct varobj *var;
  struct frame_info *fi;
  struct frame_info *old_fi = NULL;
  struct block *block;
  struct cleanup *old_chain;

  /* Fill out a varobj structure for the (root) variable being constructed. */
  var = new_root_variable ();
  old_chain = make_cleanup_free_variable (var);

  if (expression != NULL)
    {
      char *p;
      enum varobj_languages lang;

      /* Parse and evaluate the expression, filling in as much
         of the variable's data as possible */

      /* Allow creator to specify context of variable */
      if ((type == USE_CURRENT_FRAME) || (type == USE_SELECTED_FRAME))
	fi = deprecated_selected_frame;
      else
	/* FIXME: cagney/2002-11-23: This code should be doing a
	   lookup using the frame ID and not just the frame's
	   ``address''.  This, of course, means an interface change.
	   However, with out that interface change ISAs, such as the
	   ia64 with its two stacks, won't work.  Similar goes for the
	   case where there is a frameless function.  */
	fi = find_frame_addr_in_frame_chain (frame);

      /* frame = -2 means always use selected frame */
      if (type == USE_SELECTED_FRAME)
	var->root->use_selected_frame = 1;

      block = NULL;
      if (fi != NULL)
	block = get_frame_block (fi, 0);

      p = expression;
      innermost_block = NULL;
      /* Wrap the call to parse expression, so we can 
         return a sensible error. */
      if (!gdb_parse_exp_1 (&p, block, 0, &var->root->exp))
	{
	  return NULL;
	}

      /* Don't allow variables to be created for types. */
      if (var->root->exp->elts[0].opcode == OP_TYPE)
	{
	  do_cleanups (old_chain);
	  fprintf_unfiltered (gdb_stderr,
			      "Attempt to use a type name as an expression.");
	  return NULL;
	}

      var->format = variable_default_display (var);
      var->root->valid_block = innermost_block;
      var->name = savestring (expression, strlen (expression));

      /* When the frame is different from the current frame, 
         we must select the appropriate frame before parsing
         the expression, otherwise the value will not be current.
         Since select_frame is so benign, just call it for all cases. */
      if (fi != NULL)
	{
	  var->root->frame = get_frame_id (fi);
	  old_fi = deprecated_selected_frame;
	  select_frame (fi);
	}

      /* We definitively need to catch errors here.
         If evaluate_expression succeeds we got the value we wanted.
         But if it fails, we still go on with a call to evaluate_type()  */
      if (gdb_evaluate_expression (var->root->exp, &var->value))
	{
	  /* no error */
	  release_value (var->value);
	  if (VALUE_LAZY (var->value))
	    gdb_value_fetch_lazy (var->value);
	}
      else
	var->value = evaluate_type (var->root->exp);

      var->type = VALUE_TYPE (var->value);

      /* Set language info */
      lang = variable_language (var);
      var->root->lang = languages[lang];

      /* Set ourselves as our root */
      var->root->rootvar = var;

      /* Reset the selected frame */
      if (fi != NULL)
	select_frame (old_fi);
    }

  /* If the variable object name is null, that means this
     is a temporary variable, so don't install it. */

  if ((var != NULL) && (objname != NULL))
    {
      var->obj_name = savestring (objname, strlen (objname));

      /* If a varobj name is duplicated, the install will fail so
         we must clenup */
      if (!install_variable (var))
	{
	  do_cleanups (old_chain);
	  return NULL;
	}
    }

  discard_cleanups (old_chain);
  return var;
}