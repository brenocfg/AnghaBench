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
 int /*<<< orphan*/  free_current_contents ; 
 struct cleanup* make_cleanup (int /*<<< orphan*/ ,char**) ; 
 scalar_t__ strcmp (char*,char*) ; 
 int /*<<< orphan*/  ui_out_field_int (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  uiout ; 
 int varobj_delete (struct varobj*,int /*<<< orphan*/ *,int) ; 
 struct varobj* varobj_get_handle (char*) ; 
 int /*<<< orphan*/  xfree (char*) ; 
 char* xstrdup (char*) ; 

enum mi_cmd_result
mi_cmd_var_delete (char *command, char **argv, int argc)
{
  char *name;
  char *expr;
  struct varobj *var;
  int numdel;
  int children_only_p = 0;
  struct cleanup *old_cleanups;

  if (argc < 1 || argc > 2)
    error ("mi_cmd_var_delete: Usage: [-c] EXPRESSION.");

  name = xstrdup (argv[0]);
  /* Add cleanup for name. Must be free_current_contents as
     name can be reallocated */
  old_cleanups = make_cleanup (free_current_contents, &name);

  /* If we have one single argument it cannot be '-c' or any string
     starting with '-'. */
  if (argc == 1)
    {
      if (strcmp (name, "-c") == 0)
	error ("mi_cmd_var_delete: Missing required argument after '-c': variable object name");
      if (*name == '-')
	error ("mi_cmd_var_delete: Illegal variable object name");
    }

  /* If we have 2 arguments they must be '-c' followed by a string
     which would be the variable name. */
  if (argc == 2)
    {
      expr = xstrdup (argv[1]);
      if (strcmp (name, "-c") != 0)
	error ("mi_cmd_var_delete: Invalid option.");
      children_only_p = 1;
      xfree (name);
      name = xstrdup (expr);
      xfree (expr);
    }

  /* If we didn't error out, now NAME contains the name of the
     variable. */

  var = varobj_get_handle (name);

  if (var == NULL)
    error ("mi_cmd_var_delete: Variable object not found.");

  numdel = varobj_delete (var, NULL, children_only_p);

  ui_out_field_int (uiout, "ndeleted", numdel);

  do_cleanups (old_cleanups);
  return MI_CMD_DONE;
}