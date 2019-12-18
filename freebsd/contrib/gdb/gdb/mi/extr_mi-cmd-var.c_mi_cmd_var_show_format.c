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
typedef  enum varobj_display_formats { ____Placeholder_varobj_display_formats } varobj_display_formats ;
typedef  enum mi_cmd_result { ____Placeholder_mi_cmd_result } mi_cmd_result ;

/* Variables and functions */
 int MI_CMD_DONE ; 
 int /*<<< orphan*/  error (char*) ; 
 int /*<<< orphan*/  ui_out_field_string (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uiout ; 
 int /*<<< orphan*/ * varobj_format_string ; 
 int varobj_get_display_format (struct varobj*) ; 
 struct varobj* varobj_get_handle (char*) ; 

enum mi_cmd_result
mi_cmd_var_show_format (char *command, char **argv, int argc)
{
  enum varobj_display_formats format;
  struct varobj *var;

  if (argc != 1)
    error ("mi_cmd_var_show_format: Usage: NAME.");

  /* Get varobj handle, if a valid var obj name was specified */
  var = varobj_get_handle (argv[0]);
  if (var == NULL)
    error ("mi_cmd_var_show_format: Variable object not found");

  format = varobj_get_display_format (var);

  /* Report the current format */
  ui_out_field_string (uiout, "format", varobj_format_string[(int) format]);
  return MI_CMD_DONE;
}