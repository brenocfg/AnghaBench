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
typedef  enum varobj_languages { ____Placeholder_varobj_languages } varobj_languages ;
typedef  enum mi_cmd_result { ____Placeholder_mi_cmd_result } mi_cmd_result ;

/* Variables and functions */
 int MI_CMD_DONE ; 
 int /*<<< orphan*/  error (char*) ; 
 int /*<<< orphan*/  ui_out_field_string (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uiout ; 
 int /*<<< orphan*/  varobj_get_expression (struct varobj*) ; 
 struct varobj* varobj_get_handle (char*) ; 
 int varobj_get_language (struct varobj*) ; 
 int /*<<< orphan*/ * varobj_language_string ; 

enum mi_cmd_result
mi_cmd_var_info_expression (char *command, char **argv, int argc)
{
  enum varobj_languages lang;
  struct varobj *var;

  if (argc != 1)
    error ("mi_cmd_var_info_expression: Usage: NAME.");

  /* Get varobj handle, if a valid var obj name was specified */
  var = varobj_get_handle (argv[0]);
  if (var == NULL)
    error ("mi_cmd_var_info_expression: Variable object not found");

  lang = varobj_get_language (var);

  ui_out_field_string (uiout, "lang", varobj_language_string[(int) lang]);
  ui_out_field_string (uiout, "exp", varobj_get_expression (var));
  return MI_CMD_DONE;
}