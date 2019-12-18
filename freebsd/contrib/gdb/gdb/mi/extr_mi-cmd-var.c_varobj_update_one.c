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
struct varobj {int dummy; } ;
struct cleanup {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  do_cleanups (struct cleanup*) ; 
 struct cleanup* make_cleanup_ui_out_tuple_begin_end (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int mi_version (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ui_out_field_int (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ui_out_field_string (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  uiout ; 
 int /*<<< orphan*/  varobj_get_num_children (struct varobj*) ; 
 char* varobj_get_objname (struct varobj*) ; 
 char* varobj_get_type (struct varobj*) ; 
 int varobj_update (struct varobj**,struct varobj***) ; 
 int /*<<< orphan*/  xfree (struct varobj**) ; 

__attribute__((used)) static int
varobj_update_one (struct varobj *var)
{
  struct varobj **changelist;
  struct varobj **cc;
  struct cleanup *cleanup = NULL;
  int nc;

  nc = varobj_update (&var, &changelist);

  /* nc == 0 means that nothing has changed.
     nc == -1 means that an error occured in updating the variable.
     nc == -2 means the variable has changed type. */
  
  if (nc == 0)
    return 1;
  else if (nc == -1)
    {
      if (mi_version (uiout) > 1)
        cleanup = make_cleanup_ui_out_tuple_begin_end (uiout, NULL);
      ui_out_field_string (uiout, "name", varobj_get_objname(var));
      ui_out_field_string (uiout, "in_scope", "false");
      if (mi_version (uiout) > 1)
        do_cleanups (cleanup);
      return -1;
    }
  else if (nc == -2)
    {
      if (mi_version (uiout) > 1)
        cleanup = make_cleanup_ui_out_tuple_begin_end (uiout, NULL);
      ui_out_field_string (uiout, "name", varobj_get_objname (var));
      ui_out_field_string (uiout, "in_scope", "true");
      ui_out_field_string (uiout, "new_type", varobj_get_type(var));
      ui_out_field_int (uiout, "new_num_children", 
			   varobj_get_num_children(var));
      if (mi_version (uiout) > 1)
        do_cleanups (cleanup);
    }
  else
    {
      
      cc = changelist;
      while (*cc != NULL)
	{
	  if (mi_version (uiout) > 1)
	    cleanup = make_cleanup_ui_out_tuple_begin_end (uiout, NULL);
	  ui_out_field_string (uiout, "name", varobj_get_objname (*cc));
	  ui_out_field_string (uiout, "in_scope", "true");
	  ui_out_field_string (uiout, "type_changed", "false");
	  if (mi_version (uiout) > 1)
	    do_cleanups (cleanup);
	  cc++;
	}
      xfree (changelist);
      return 1;
    }
  return 1;
}