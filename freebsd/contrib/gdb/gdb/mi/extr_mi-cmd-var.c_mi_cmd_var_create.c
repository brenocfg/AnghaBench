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
typedef  enum varobj_type { ____Placeholder_varobj_type } varobj_type ;
typedef  enum mi_cmd_result { ____Placeholder_mi_cmd_result } mi_cmd_result ;
typedef  int /*<<< orphan*/  CORE_ADDR ;

/* Variables and functions */
 int MI_CMD_DONE ; 
 int USE_CURRENT_FRAME ; 
 int USE_SELECTED_FRAME ; 
 int USE_SPECIFIED_FRAME ; 
 int /*<<< orphan*/  do_cleanups (struct cleanup*) ; 
 int /*<<< orphan*/  error (char*) ; 
 int /*<<< orphan*/  fprintf_unfiltered (int /*<<< orphan*/ ,char*,char*,char*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  free_current_contents ; 
 int /*<<< orphan*/  gdb_stdlog ; 
 int /*<<< orphan*/  isalpha (char) ; 
 struct cleanup* make_cleanup (int /*<<< orphan*/  (*) (char*),...) ; 
 int /*<<< orphan*/  paddr (int /*<<< orphan*/ ) ; 
 scalar_t__ strcmp (char*,char*) ; 
 int /*<<< orphan*/  string_to_core_addr (char*) ; 
 int /*<<< orphan*/  ui_out_field_int (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ui_out_field_string (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  uiout ; 
 struct varobj* varobj_create (char*,char*,int /*<<< orphan*/ ,int) ; 
 char* varobj_gen_name () ; 
 int /*<<< orphan*/  varobj_get_num_children (struct varobj*) ; 
 char* varobj_get_type (struct varobj*) ; 
 scalar_t__ varobjdebug ; 
 int /*<<< orphan*/  xfree (char*) ; 
 char* xstrdup (char*) ; 

enum mi_cmd_result
mi_cmd_var_create (char *command, char **argv, int argc)
{
  CORE_ADDR frameaddr = 0;
  struct varobj *var;
  char *name;
  char *frame;
  char *expr;
  char *type;
  struct cleanup *old_cleanups;
  enum varobj_type var_type;

  if (argc != 3)
    {
      /*      xasprintf (&mi_error_message,
         "mi_cmd_var_create: Usage: .");
         return MI_CMD_ERROR; */
      error ("mi_cmd_var_create: Usage: NAME FRAME EXPRESSION.");
    }

  name = xstrdup (argv[0]);
  /* Add cleanup for name. Must be free_current_contents as
     name can be reallocated */
  old_cleanups = make_cleanup (free_current_contents, &name);

  frame = xstrdup (argv[1]);
  old_cleanups = make_cleanup (xfree, frame);

  expr = xstrdup (argv[2]);

  if (strcmp (name, "-") == 0)
    {
      xfree (name);
      name = varobj_gen_name ();
    }
  else if (!isalpha (*name))
    error ("mi_cmd_var_create: name of object must begin with a letter");

  if (strcmp (frame, "*") == 0)
    var_type = USE_CURRENT_FRAME;
  else if (strcmp (frame, "@") == 0)
    var_type = USE_SELECTED_FRAME;  
  else
    {
      var_type = USE_SPECIFIED_FRAME;
      frameaddr = string_to_core_addr (frame);
    }

  if (varobjdebug)
    fprintf_unfiltered (gdb_stdlog,
		    "Name=\"%s\", Frame=\"%s\" (0x%s), Expression=\"%s\"\n",
			name, frame, paddr (frameaddr), expr);

  var = varobj_create (name, expr, frameaddr, var_type);

  if (var == NULL)
    error ("mi_cmd_var_create: unable to create variable object");

  ui_out_field_string (uiout, "name", name);
  ui_out_field_int (uiout, "numchild", varobj_get_num_children (var));
  type = varobj_get_type (var);
  if (type == NULL)
    ui_out_field_string (uiout, "type", "");
  else
    {
      ui_out_field_string (uiout, "type", type);
      xfree (type);
    }

  do_cleanups (old_cleanups);
  return MI_CMD_DONE;
}