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
 int FORMAT_BINARY ; 
 int FORMAT_DECIMAL ; 
 int FORMAT_HEXADECIMAL ; 
 int FORMAT_NATURAL ; 
 int FORMAT_OCTAL ; 
 int MI_CMD_DONE ; 
 int /*<<< orphan*/  error (char*) ; 
 int strlen (char*) ; 
 scalar_t__ strncmp (char*,char*,int) ; 
 int /*<<< orphan*/  ui_out_field_string (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uiout ; 
 int /*<<< orphan*/ * varobj_format_string ; 
 struct varobj* varobj_get_handle (char*) ; 
 int /*<<< orphan*/  varobj_set_display_format (struct varobj*,int) ; 
 char* xstrdup (char*) ; 

enum mi_cmd_result
mi_cmd_var_set_format (char *command, char **argv, int argc)
{
  enum varobj_display_formats format;
  int len;
  struct varobj *var;
  char *formspec;

  if (argc != 2)
    error ("mi_cmd_var_set_format: Usage: NAME FORMAT.");

  /* Get varobj handle, if a valid var obj name was specified */
  var = varobj_get_handle (argv[0]);

  if (var == NULL)
    error ("mi_cmd_var_set_format: Variable object not found");

  formspec = xstrdup (argv[1]);
  if (formspec == NULL)
    error ("mi_cmd_var_set_format: Must specify the format as: \"natural\", \"binary\", \"decimal\", \"hexadecimal\", or \"octal\"");

  len = strlen (formspec);

  if (strncmp (formspec, "natural", len) == 0)
    format = FORMAT_NATURAL;
  else if (strncmp (formspec, "binary", len) == 0)
    format = FORMAT_BINARY;
  else if (strncmp (formspec, "decimal", len) == 0)
    format = FORMAT_DECIMAL;
  else if (strncmp (formspec, "hexadecimal", len) == 0)
    format = FORMAT_HEXADECIMAL;
  else if (strncmp (formspec, "octal", len) == 0)
    format = FORMAT_OCTAL;
  else
    error ("mi_cmd_var_set_format: Unknown display format: must be: \"natural\", \"binary\", \"decimal\", \"hexadecimal\", or \"octal\"");

  /* Set the format of VAR to given format */
  varobj_set_display_format (var, format);

  /* Report the new current format */
  ui_out_field_string (uiout, "format", varobj_format_string[(int) format]);
  return MI_CMD_DONE;
}