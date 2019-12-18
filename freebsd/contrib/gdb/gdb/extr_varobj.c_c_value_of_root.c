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
struct varobj {int error; TYPE_1__* root; } ;
struct value {int dummy; } ;
struct frame_info {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  exp; int /*<<< orphan*/  frame; int /*<<< orphan*/ * valid_block; struct varobj* rootvar; } ;

/* Variables and functions */
 scalar_t__ VALUE_LAZY (struct value*) ; 
 struct frame_info* frame_find_by_id (int /*<<< orphan*/ ) ; 
 scalar_t__ gdb_evaluate_expression (int /*<<< orphan*/ ,struct value**) ; 
 int /*<<< orphan*/  gdb_value_fetch_lazy (struct value*) ; 
 int /*<<< orphan*/  reinit_frame_cache () ; 
 int /*<<< orphan*/  release_value (struct value*) ; 
 int /*<<< orphan*/  select_frame (struct frame_info*) ; 

__attribute__((used)) static struct value *
c_value_of_root (struct varobj **var_handle)
{
  struct value *new_val;
  struct varobj *var = *var_handle;
  struct frame_info *fi;
  int within_scope;

  /*  Only root variables can be updated... */
  if (var->root->rootvar != var)
    /* Not a root var */
    return NULL;


  /* Determine whether the variable is still around. */
  if (var->root->valid_block == NULL)
    within_scope = 1;
  else
    {
      reinit_frame_cache ();
      fi = frame_find_by_id (var->root->frame);
      within_scope = fi != NULL;
      /* FIXME: select_frame could fail */
      if (within_scope)
	select_frame (fi);
    }

  if (within_scope)
    {
      /* We need to catch errors here, because if evaluate
         expression fails we just want to make val->error = 1 and
         go on */
      if (gdb_evaluate_expression (var->root->exp, &new_val))
	{
	  if (VALUE_LAZY (new_val))
	    {
	      /* We need to catch errors because if
	         value_fetch_lazy fails we still want to continue
	         (after making val->error = 1) */
	      /* FIXME: Shouldn't be using VALUE_CONTENTS?  The
	         comment on value_fetch_lazy() says it is only
	         called from the macro... */
	      if (!gdb_value_fetch_lazy (new_val))
		var->error = 1;
	      else
		var->error = 0;
	    }
	}
      else
	var->error = 1;

      release_value (new_val);
      return new_val;
    }

  return NULL;
}