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
typedef  enum mi_cmd_result { ____Placeholder_mi_cmd_result } mi_cmd_result ;

/* Variables and functions */
 int MI_CMD_DONE ; 
 int /*<<< orphan*/  do_cleanups (struct cleanup*) ; 
 int /*<<< orphan*/  error (char*) ; 
 struct cleanup* make_cleanup_ui_out_list_begin_end (int /*<<< orphan*/ ,char*) ; 
 struct cleanup* make_cleanup_ui_out_tuple_begin_end (int /*<<< orphan*/ ,char*) ; 
 int mi_version (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uiout ; 
 struct varobj* varobj_get_handle (char*) ; 
 int varobj_list (struct varobj***) ; 
 int /*<<< orphan*/  varobj_update_one (struct varobj*) ; 
 int /*<<< orphan*/  xfree (struct varobj**) ; 

enum mi_cmd_result
mi_cmd_var_update (char *command, char **argv, int argc)
{
  struct varobj *var;
  struct varobj **rootlist;
  struct varobj **cr;
  struct cleanup *cleanup;
  char *name;
  int nv;

  if (argc != 1)
    error ("mi_cmd_var_update: Usage: NAME.");

  name = argv[0];

  /* Check if the parameter is a "*" which means that we want
     to update all variables */

  if ((*name == '*') && (*(name + 1) == '\0'))
    {
      nv = varobj_list (&rootlist);
      if (mi_version (uiout) <= 1)
        cleanup = make_cleanup_ui_out_tuple_begin_end (uiout, "changelist");
      else
        cleanup = make_cleanup_ui_out_list_begin_end (uiout, "changelist");
      if (nv <= 0)
	{
	  do_cleanups (cleanup);
	  return MI_CMD_DONE;
	}
      cr = rootlist;
      while (*cr != NULL)
	{
	  varobj_update_one (*cr);
	  cr++;
	}
      xfree (rootlist);
      do_cleanups (cleanup);
    }
  else
    {
      /* Get varobj handle, if a valid var obj name was specified */
      var = varobj_get_handle (name);
      if (var == NULL)
	error ("mi_cmd_var_update: Variable object not found");

      if (mi_version (uiout) <= 1)
        cleanup = make_cleanup_ui_out_tuple_begin_end (uiout, "changelist");
      else
        cleanup = make_cleanup_ui_out_list_begin_end (uiout, "changelist");
      varobj_update_one (var);
      do_cleanups (cleanup);
    }
    return MI_CMD_DONE;
}